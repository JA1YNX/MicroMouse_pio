#pragma once

#include <Arduino.h>
#include <Ticker.h>

// variables for high resolution timer interrupt
/*volatile int interruptCounter;
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;*/

class BNO055{
public:
    BNO055(uint16_t _internal);

    //度数法で値を取得
    float getDegrees();

    //受信割り込み
    void tick();
    
private:
    uint16_t internal;
    Ticker ticker;
    //値をリクエスト
    void requestValue();

    //レジスタ1バイト分を書き込む
    void writeByte(unsigned char reg_add, unsigned char value);

    //値を更新
    void updateValue();
    
    //現在の方向をゼロとする．
    void reset(int value = 0);

    //現在の値（生の値）
    int16_t raw_value = 0;

    //零点
    int zero_point = 0;

    //
    int getValue();
    

    //分解能
    const int RESOLUTION = 5760;

    //送信
    const char START_BYTE = 0xAA; 
    const char RESPONSE_BYTE = 0xBB;
    const char WRITE_BYTE = 0x00;
    const char READ_BYTE = 0x01;

    //EULER角が保持されたレジスタの先頭のアドレス
    const char TARGET_REGISTER = 0x1A;

    //受信バッファー
    char receive_buffer[16];

    //受信プロセス
    enum RECEIVE_PROCESS{
        STARTING, //0xBBを受信
        SET_LENGTH, //長さを受信
        RECEIVING //値を受信
    };

    int receive_process = STARTING;

    unsigned int receive_index = 0;
    unsigned int receive_length = 0;

    bool started = false;
};