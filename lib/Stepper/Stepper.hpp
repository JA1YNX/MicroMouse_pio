#pragma once

#include <Arduino.h>
#include "uMouse_setting.hpp"

constexpr uint8_t resolution = 10;
constexpr uint8_t freq = 1000;

#if USING_707x // main.cppやどこかでマクロ定義によってやっていただければ

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

} Pin_SLA707x;

enum driveMode{
    dual_Mode8,
    dual_ModeF,
    onetwo_Half,
    onetwo_ModeF
};

class Stepper
{
private:
    Pin_SLA707x pin;
    driveMode d_Mode;

public:
    Stepper(Pin_SLA707x _pin, driveMode _dm);
    
    void set_DriveMode(driveMode _dm);

    void rotate(float _duty);
};

#else
typedef struct{
    uint8_t p_BSEL;
    uint8_t p_inA;
    uint8_t p_inA_;
    uint8_t p_inB;
    uint8_t p_inB_;
    uint8_t p_ref;
    uint8_t p_reset;
    uint8_t p_SYNC;
    uint8_t p_Flag;//秋月ではMRという表記のを買えるが、中身はMPRなので注意

} Pin_SLA708x;

class Stepper
{
private:
    Pin_SLA708x pin;
    bool sync;
    bool bsel;

public:
    Stepper(Pin_SLA708x _pin, bool _sync, bool _bsel);
    
    void set_DriveMode(bool _sync, bool _bsel);
    void rotate(float _duty);
};
#endif