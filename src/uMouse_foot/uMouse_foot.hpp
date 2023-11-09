#pragma once

#include <Arduino.h>
#include "Stepper/Stepper.hpp"

enum Move_dir{
    none,
    forward,
    right,
    left,
    back
};

class uMouse_foot{
public:
    uMouse_foot();

    void get_pos(float* _currentPos);
    void go_next(Move_dir _last_md, Vector2i& _current, Pos_info* next);// return next posinfo

    void go_forward();
    void go_right();
    void go_left();
    void go_back();

private:
    uint16_t tire_radius = 25;


    Stepper MotorR;
    Stepper MotorL;
}