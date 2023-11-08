#pragma once

#define BNOrate 20

#define USING_707x (true)

#define pin_MotorR 15

constexpr uint8_t resolution = 10;
const uint16_t resolution10 = pow(2.0f, resolution);//10進

constexpr uint8_t p_M1_1 = 2;
constexpr uint8_t p_M2_1 = 4;
constexpr uint8_t p_M3_1 = 16;
constexpr uint8_t p_CLOCK_1 = 13;
constexpr uint8_t p_ref = 15;
constexpr uint8_t p_reset_1 = 21;
constexpr uint8_t p_dir_1 = 22;
constexpr uint8_t p_SYNC_1 = 23;
constexpr uint8_t p_Flag_1 = 34;

constexpr uint8_t p_M1_2 = 2;
constexpr uint8_t p_M2_2 = 4;
constexpr uint8_t p_M3_2 = 16;
constexpr uint8_t p_CLOCK_2 = 13;
constexpr uint8_t p_ref_2 = 15;
constexpr uint8_t p_reset_2 = 21;
constexpr uint8_t p_dir_2 = 22;
constexpr uint8_t p_SYNC_2 = 23;
constexpr uint8_t p_Flag_2 = 34;