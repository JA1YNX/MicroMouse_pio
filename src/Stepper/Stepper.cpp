#include "Stepper.hpp"

#if USING_707x

Stepper::Stepper(Pin_SLA707x _pin, driveMode _dm):pin(_pin), d_Mode(_dm)
{
    pinMode(pin.p_M1, OUTPUT);
    pinMode(pin.p_M2, OUTPUT);
    pinMode(pin.p_M3, OUTPUT);
    pinMode(pin.p_CLOCK,OUTPUT);
    pinMode(pin.p_ref, OUTPUT);
    pinMode(pin.p_reset, OUTPUT);
    pinMode(pin.p_dir, OUTPUT);
    pinMode(pin.p_SYNC, OUTPUT);
    pinMode(pin.p_Flag, INPUT);

    digitalWrite(pin.p_reset, 0);
    digitalWrite(pin.p_CLOCK, 0);
    digitalWrite(pin.p_ref, 0);
    digitalWrite(pin.p_SYNC, 1);
    digitalWrite(pin.p_dir, 0);

    ledcSetup(0, freq, resolution);
    ledcAttachPin(pin.p_CLOCK, 0);
    ledcWrite(0, 0);

    //bool driveMode[3] = {d_Mode%4%2, d_Mode%4/2, d_Mode/4};
    //digitalWrite(pin.p_M1, driveMode[0]);
    //digitalWrite(pin.p_M2, driveMode[1]);
    //digitalWrite(pin.p_M3, driveMode[2]);

    digitalWrite(pin.p_M1, 1);
    digitalWrite(pin.p_M2, 0);
    digitalWrite(pin.p_M3, 0);
}

void Stepper::set_DriveMode(driveMode _dm){
    d_Mode = _dm;
    bool driveMode[3] = {d_Mode%4%2, d_Mode%4/2, d_Mode/4};
    digitalWrite(pin.p_M1, driveMode[0]);
    digitalWrite(pin.p_M2, driveMode[1]);
    digitalWrite(pin.p_M3, driveMode[2]);
}

void Stepper::rotate(float _duty){
    digitalWrite(pin.p_dir, _duty >= 0);
    ledcWrite(0, (int)(abs(_duty)*resolution));
}

#else

Stepper::Stepper(Pin_SLA708x _pin, bool _sync, bool _bsel):pin(_pin), sync(_sync), bsel(_bsel)
{
    pinMode(pin.p_BSEL, OUTPUT);
    pinMode(pin.p_inA, OUTPUT);
    pinMode(pin.p_inA_, OUTPUT);
    pinMode(pin.p_inB,OUTPUT);
    pinMode(pin.p_inB_, OUTPUT);
    pinMode(pin.p_ref, OUTPUT);
    pinMode(pin.p_reset, OUTPUT);
    pinMode(pin.p_SYNC, OUTPUT);
    pinMode(pin.p_Flag, INPUT);

    digitalWrite(pin.p_BSEL, 0);
    digitalWrite(pin.p_inA, 0);
    digitalWrite(pin.p_inA_, 0);
    digitalWrite(pin.p_inB, 0);
    digitalWrite(pin.p_inB_, 0);
    digitalWrite(pin.p_ref, 0);
    digitalWrite(pin.p_reset, 0);
    digitalWrite(pin.p_SYNC, 0);
    
    pwmSetup(freq);

    ledcAttachPin(pin.p_inA, chA);
    ledcAttachPin(pin.p_inA_, chA_);
    ledcAttachPin(pin.p_inB, chB);
    ledcAttachPin(pin.p_inB_, chB_);
    
    rotate(0);

    setDriveMode(sync, bsel);
}

void Stepper::setDriveMode(bool _sync, bool _bsel){
    sync = _sync;
    bsel = _bsel;
    digitalWrite(pin.p_SYNC, sync);
    digitalWrite(pin.p_BSEL, bsel);
}

void Stepper::rotate(float _duty){
    ledcWrite(chA, _duty >= 0 ? (int)(_duty*resolution10) : 0);
    ledcWrite(chA_, _duty < 0 ? (int)(_duty*resolution10) : 0);
    ledcWrite(chB, _duty >= 0 ? 0 :(int)(_duty*resolution10));
    ledcWrite(chB_, _duty < 0 ? 0 :(int)(_duty*resolution10));
}

void Stepper::pwmSetup(uint16_t _freq){
    freq = _freq;
    ledcSetup(0, freq, resolution);
    ledcSetup(1, freq, resolution);
    ledcSetup(2, freq, resolution);
    ledcSetup(3, freq, resolution);
}

#endif