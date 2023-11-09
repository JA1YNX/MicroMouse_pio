#pragma once

#include <Arduino.h>
#include "Stepper/Stepper.hpp"
#include "BNO055/BNO055.hpp"

enum Move_dir{
    none,
    forward,
    right,
    left,
    back
};

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