#pragma once

#include <Arduino.h>
#include <ArduinoEigen.h>
#include <FS.h>
#include <SPIFFS.h>

#include "uMouse_foot/uMouse_foot.hpp"
#include "uMouse_setting.hpp"
#include "BNO055/BNO055.hpp"

using namespace std;
using namespace Eigen;
using namespace fs;

const String path = "/uMouseMap.txt";

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
    Move_dir movedDir;
} Pos_info;

class MicroMouse_oswELE
{
private:
    Pos_info posInfo[16][16]; //(x, y)に対応
    void get_neighbor_Pos_info(Vector2i& _current, Pos_info* _neighbors);

    BNO055 imu;
    uMouse_foot ashi;
    
public:
    MicroMouse_oswELE(Pin_SLA707x _pin_motorR, Pin_SLA707x _pin_motorL, driveMode _dm);
    
};