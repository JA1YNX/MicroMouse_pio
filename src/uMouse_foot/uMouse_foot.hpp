#pragma once

#include <Arduino.h>
#include "Stepper/Stepper.hpp"
#include "BNO055/BNO055.hpp"

typedef struct {
    const int none = 0;
    const int forward = 1;
    const int right = 2;
    const int left = 4;
    const int back = 8;
}Move_dir ;

class uMouse_foot{
public:
    uMouse_foot(Pin_SLA707x _p_ML, Pin_SLA707x _p_MR, driveMode _dm);

    void get_pos(float* _currentPos);
    
    void go_forward();
    void go_right();
    void go_left();
    void go_back();

private:
    uint16_t tire_radius = 25;

    Stepper MotorR;
    Stepper MotorL;

    BNO055 imu;
};