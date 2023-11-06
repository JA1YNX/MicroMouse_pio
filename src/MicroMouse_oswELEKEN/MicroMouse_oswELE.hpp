#pragma once

#include <Arduino.h>
#include <ArduinoEigen.h>
#include <FS.h>
#include <SPIFFS.h>
#include "Stepper/Stepper.hpp"
#include "uMouse_setting.hpp"

using namespace std;
using namespace Eigen;
using namespace fs;

const String path = "/uMouseMap.txt";

enum Moved_dir{
    none,
    forward,
    right,
    left,
    back
};

typedef struct{
    int none = 0;
    int B = 1;
    int L = 2;
    int LB = 3;
    int F = 4;
    int FB = 5;
    int FL = 6;
    int FLB = 7;
    int R = 8;
    int RB = 9;
    int RL = 10;
    int RLB = 11;
    int RF = 12;
    int RFB = 13;
    int RFL = 14;
    int all = 15;
}WallType;

typedef struct {
    Vector2i pos;//2次元ベクトル
    int step;
    WallType wallType;
    Moved_dir movedDir;
} Pos_info;

class MicroMouse_oswELE
{
private:
    Pos_info posInfo[16][16]; //(x, y)に対応
    void get_neighbor_Pos_info(Vector2i& _current, Pos_info* _neighbors);

    Stepper MotorR;
    Stepper MotorL;
    
public:
    MicroMouse_oswELE(Pin_SLA707x _pin_motorR, Pin_SLA707x _pin_motorL, driveMode _dm);
    void go_next(Moved_dir _last_md, Vector2i& _current, Pos_info* next);// return next posinfo
};