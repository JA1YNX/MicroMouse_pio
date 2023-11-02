#pragma once

#include <Arduino.h>

typedef struct{
    uint8_t p_M1;
    uint8_t p_M2;
    uint8_t p_M3;
    uint8_t p_CLOCK;
    uint8_t p_ref;
    uint8_t p_reset;
    uint8_t p_dir;
    uint8_t p_SYNC;
    uint8_t p_Flag;

} Pin_SLA70xx;

enum driveMode{
    dual_Mode8,
    dual_ModeF,
    onetwo_Half,
    onetwo_ModeF
};

class Stepper
{
private:
    Pin_SLA70xx pin;
    driveMode d_Mode;

public:
    Stepper(Pin_SLA70xx _pin, driveMode _dm);
    
    void go_f();
    void go_r();
    void go_l();
    void go_b();
};