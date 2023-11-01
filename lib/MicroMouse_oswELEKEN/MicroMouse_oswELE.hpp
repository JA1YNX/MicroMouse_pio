#pragma once

#include <ArduinoEigen.h>
using namespace std;
using namespace Eigen;

typedef struct{
    int none = 0;
    int forward = 1;
    int right = 2;
    int left = 3;
    int back = 4;
}Moved_dir;

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
    Vector2d pos;//2次元ベクトル
    int step;
    WallType wallType;
    Moved_dir movedDir;
} Pos_info;

class MicroMouse_oswELE
{
private:
    Pos_info posInfo[16][16]; //(x, y)に対応
    void get_neighbor_Pos_info(Pos_info& _current, Pos_info* _neighbors);

    void go_f();
    void go_r();
    void go_l();
    void go_b();
    
public:
    MicroMouse_oswELE();
    void go_next(Moved_dir _last_md,Pos_info& _current, Pos_info* next);// return next posinfo
};