#include "Stepper.hpp"

Stepper::Stepper(Pin_SLA70xx _pin):pin(_pin)
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

    ledcSetup(0, 1000, 10);

    ledcAttachPin(pin.p_CLOCK, 0);

    
    bool driveMode[3] = {d_Mode%4%2, d_Mode%4/2, d_Mode/4};
    digitalWrite(pin.p_M1, 0);
    digitalWrite(pin.p_M2, 0);
    digitalWrite(pin.p_M3, 0);
}

void Stepper::go_f(){

}

void Stepper::go_r(){

}

void Stepper::go_l(){

}

void Stepper::go_b(){

}