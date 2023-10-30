#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;

typedef struct{
    bool is;
    Eigen::Vector2d pos;
}Is_Wall;

Is_Wall wall[16][16];//(0,0),,,(15,0),(0,1),,,

const int map_width = 16 * 2;
const int map_height = 16 * 2;

void KabeNobashi(Is_Wall* _wall){
    for(int x = 0; x < 32; x++){
        *(_wall + x) = {true,{x,0}};
        *(_wall + 32 * 31 + x) = {true,{x,31}};
    }
    for(int y = 0; y < 32; y++){
        *(_wall + 32 * y) = {true,{0,y}};
        *(_wall + 32 * 31 + y) = {true,{31,y}};
    }
}

void show_wall(Is_Wall* _wall){
    for(int y = 0; y < 32; y++){
        for(int x = 0; x < 32; x++){
            //bool is = *(_wall+ x + 32 * y)->is;
            //printf("%d",is);
        }
        cout << "\r\n";
    }
}
/*
int main(){
    KabeNobashi(&wall[0][0]);
    show_wall(&wall[0][0]);

    return 0;
}*/