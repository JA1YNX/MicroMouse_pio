/*

#include "MicroMouse_oswELE.hpp"

MicroMouse_oswELE::MicroMouse_oswELE(){
    //init pos
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            posInfo[x][y].pos = Vector2d::Constant(x,y);
        }
    }
    
    //init step map
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            posInfo[7 - x][7 - y].step = x + y;
            posInfo[8 + x][7 - y].step = x + y;
            posInfo[7 - x][8 + y].step = x + y;
            posInfo[8 + x][8 + y].step = x + y;
        }
    }
}

// F R L Bの順で返す
void MicroMouse_oswELE::get_neighbor_Pos_info(Pos_info& _current, Pos_info* _neighbors){

}

//_last_moveddirで一つ飛ばしたい。
void MicroMouse_oswELE::go_next(Moved_dir _last_md, Pos_info& _current, Pos_info* _next){
    Pos_info nexts[4];
    get_neighbor_Pos_info(_current, &nexts[0]);

    switch (_last_md)
    {
    case Moved_dir::forward:
        if(nexts[0].step > nexts[1].step){
            MotorR.rotate(0.5f);
            MotorL.rotate(0.5f);
        }
        
        break;
    
    default:
        break;
    }
}

*/