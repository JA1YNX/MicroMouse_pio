#include "MicroMouse_oswELE.hpp"

MicroMouse_oswELE::MicroMouse_oswELE()
{
    //init pos
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            posInfo[x][y].pos = Vector2d::Constant(x,y);
        }
    }
    
    //init step map
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            Pos_info[7 - x][7 - y].step = x + y;
            Pos_info[8 + x][7 - y].step = x + y;
            Pos_info[7 - x][8 + y].step = x + y;
            Pos_info[8 + x][8 + y].step = x + y;
        }
    }
}