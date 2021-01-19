#include "motor.h"
#include "controlpanel.h"
#include "minimax.h"


#define LIMITSWITCHPIN 4
//TicTacToeBoard board;

Motor ymotor(12,11);
Motor xmotor(7,6);

void toggle(bool state){
  Serial.println("Hello");
}
ControlPanel cp(1, 2, 3, 4, 5, &toggle, &setup);

void setup(){
 xmotor.setSpeed(200);
 xmotor.setGoal(8000);
 ymotor.setGoal(800);
}

void loop(){
  ymotor.run();
}
