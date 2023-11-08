#include "MicroMouse_oswELEKEN/MicroMouse_oswELE.hpp"

MicroMouse_oswELE::MicroMouse_oswELE(Pin_SLA707x _pin_motorR, Pin_SLA707x _pin_motorL, driveMode _dm): MotorR(_pin_motorR, _dm), MotorL(_pin_motorL,_dm){
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

    SPIFFS.begin();
    
    File _f = SPIFFS.open(path, FILE_WRITE);
    for(int y = 0; y < 16; y++){
        for(int x = 0; x < 16; x++){
            _f.write(&posInfo[x][y].pos.x(), sizeof(posInfo[x][y]));
        }
    }
    
}

// F R L Bの順で返す
void MicroMouse_oswELE::get_neighbor_Pos_info(Vector2i& _current, Pos_info* _neighbors){
    *(_neighbors)       = posInfo[_current.x()  ][_current.y()+1];
    *(_neighbors + 1)   = posInfo[_current.x()+1][_current.y()];
    *(_neighbors + 2)   = posInfo[_current.x()-1][_current.y()];
    *(_neighbors + 3)   = posInfo[_current.x()  ][_current.y()-1];
}

//_last_moveddirで一つ飛ばしたい。
void MicroMouse_oswELE::go_next(Moved_dir _last_md, Vector2i& _current, Pos_info* _next){
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