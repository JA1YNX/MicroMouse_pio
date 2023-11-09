#include "uMouse_foot/uMouse_foot.hpp"

uMouse_foot::uMouse_foot():MotorL(Stepper()), MotorR(Stepper()){

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

//_last_moveddirで一つ飛ばしたい。
void UMouse_foot::go_next(Move_dir _last_md, Vector2i& _current, Pos_info* _next){
    Pos_info nexts[4];
    get_neighbor_Pos_info(_current, &nexts[0]);

    Move_dir nextDir;

    switch (_last_md)
    {
    case Move_dir::forward:
        nexts[0].step > nexts[1].step ? nextDir = Move_dir::forward : nextDir = Move_dir::right;
        nexts[0].step > nexts[2].step ? nextDir = Move_dir::forward : nextDir = Move_dir::left;
        if(nextDir != Move_dir::forward){
            nexts[1].step > nexts[2].step ? nextDir = Move_dir::right : nextDir = Move_dir::left;
        }
        go_forward();
        break;
    
    case Move_dir::right:
        nexts[0].step > nexts[1].step ? nextDir = Move_dir::right : nextDir = Move_dir::back;
        nexts[0].step > nexts[2].step ? nextDir = Move_dir::right : nextDir = Move_dir::forward;
        if(nextDir != Move_dir::right){
            nexts[1].step > nexts[2].step ? nextDir = Move_dir::back : nextDir = Move_dir::forward;
        }
        go_right();
        break;

    case Move_dir::left:
        nexts[0].step > nexts[1].step ? nextDir = Move_dir::left : nextDir = Move_dir::forward;
        nexts[0].step > nexts[2].step ? nextDir = Move_dir::left : nextDir = Move_dir::back;
        if(nextDir != Move_dir::left){
            nexts[1].step > nexts[2].step ? nextDir = Move_dir::forward : nextDir = Move_dir::back;
        }
        go_left();
        break;
    
    default://::back
        nexts[0].step > nexts[1].step ? nextDir = Move_dir::back : nextDir = Move_dir::left;
        nexts[0].step > nexts[2].step ? nextDir = Move_dir::back : nextDir = Move_dir::right;
        if(nextDir != Move_dir::back){
            nexts[1].step > nexts[2].step ? nextDir = Move_dir::left : nextDir = Move_dir::right;
        }
        go_back();
        break;
    }
}