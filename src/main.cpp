#include <Arduino.h>
#include "Stepper/Stepper.hpp"

uint8_t p_M1 = 2;
uint8_t p_M2 = 4;
uint8_t p_M3 = 16;
uint8_t p_CLOCK = 13;
uint8_t p_ref = 15;
uint8_t p_reset = 21;
uint8_t p_dir = 22;
uint8_t p_SYNC= 23;
uint8_t p_Flag = 34;


void u_main();

void setup() {
  u_main();
}

void loop() {}

void u_main(){
  Stepper m({6, 9, 10, 13, 15, 21, 22, 23}, driveMode::dual_ModeF);

}