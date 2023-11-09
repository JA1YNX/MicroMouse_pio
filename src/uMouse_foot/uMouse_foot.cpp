#include "uMouse_foot/uMouse_foot.hpp"

uMouse_foot::uMouse_foot(Pin_SLA707x _p_ML, Pin_SLA707x _p_MR, driveMode _dm):MotorL(Stepper(_p_ML, _dm)), MotorR(Stepper(_p_MR, _dm)), imu(BNO055(BNOrate))
{

}

void uMouse_foot::go_forward(){
    MotorL.rotate(0.5f);
    MotorR.rotate(0.5f);
}

void uMouse_foot::go_right(){
    while (imu.getDegrees()>= -91.0f && imu.getDegrees() <= -89.0f)
    {
        MotorL.rotate(0.5f);
        MotorR.rotate(-0.5f);   
    }

    go_forward();
}

void uMouse_foot::go_left(){
    while (imu.getDegrees()>= 89.0f && imu.getDegrees() <= 91.0f)
    {
        MotorL.rotate(0.5f);
        MotorR.rotate(-0.5f);   
    }

    go_forward();
}


void uMouse_foot::go_left(){
    while (imu.getDegrees()>= 179.0f && imu.getDegrees() <= -179.0f)
    {
        MotorL.rotate(0.5f);
        MotorR.rotate(-0.5f);   
    }

    go_forward();
}

void uMouse_foot::get_pos(float* _currentPos){
    *(_currentPos) = (float)MotorL.get_numStepped() * (float)tire_radius * M_PI;
    *(_currentPos + 1) = (float)MotorR.get_numStepped() * (float)tire_radius * M_PI;
}