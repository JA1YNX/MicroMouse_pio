#include "BNO055/BNO055.hpp"
#include <math.h>

BNO055::BNO055(uint16_t _internal):internal(_internal)
{
    Serial1.begin(115200);
    
    writeByte(0x3D, 0x0C);

    delay(20);
    
    ticker.attach_ms(internal, [&]{interrupt();});

    // generate timer (Timer Number, 80MHz / divider, count up=true,down=false)
    //timer is generated hear and defined as global
    /*timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &this->interrupt, true);
    timerAlarmWrite(timer, internal, true);
    timerAlarmEnable(timer);*/

    while(!started){
        delayMicroseconds(1);
    }
    reset();
}

void BNO055::writeByte(unsigned char reg_add, unsigned char value){
    char data[] = {START_BYTE, WRITE_BYTE, reg_add, 0x01, value};
    Serial1.write(data, 5);
}

void BNO055::requestValue(){
    char data[] = {START_BYTE, READ_BYTE, TARGET_REGISTER, 0x02};
    Serial1.write(data, 4);
    ticker.attach_ms(internal, [this]{interrupt();});
}

void BNO055::interrupt(){
    char c;
    Serial1.read(&c, 1);

    switch (receive_process)
    {
    case STARTING:
        if(c == RESPONSE_BYTE){
            receive_process = SET_LENGTH;
        }
        break;
    
    case SET_LENGTH:
        receive_length = c;
        receive_index = 0;
        receive_process = RECEIVING;
        break;

    case RECEIVING:
        receive_buffer[receive_index] = c;
        receive_index++;

        if(receive_index == receive_length){
            receive_process = STARTING;
            if (receive_length == 2){
                updateValue();
            }
        }
        break;
    
    default:
        break;
    }
}


void BNO055::updateValue(){
    int new_value = (int16_t(receive_buffer[1]) << 8) | int16_t(receive_buffer[0]);

    if(raw_value > 3 * RESOLUTION / 4 && new_value < RESOLUTION / 4){
        zero_point -= RESOLUTION;
    }else if(raw_value < RESOLUTION / 4 && new_value > 3 * RESOLUTION / 4){
        zero_point += RESOLUTION;
    }

    raw_value = new_value;
    started = true;
}

void BNO055::reset(int value){
    zero_point = raw_value - value;
}


int BNO055::getValue(){
    return raw_value - zero_point;
}

float BNO055::getDegrees(){
    return 360.0f * getValue() / RESOLUTION;
}