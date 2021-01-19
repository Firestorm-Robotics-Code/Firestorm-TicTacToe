#include "motor.h"
#include "analogReadFast.h"
#include "joystick.h"
#include "minimax.h"


#define TRIGGERPIN 4
//TicTacToeBoard board;

Motor ymotor(12,11);
Motor xmotor(7,6);
void setup(){
 xmotor.setSpeed(200);
 xmotor.setGoal(8000);
 ymotor.setGoal(800);
}

void loop(){
  ymotor.run();
}
