#include "motor.cpp"
#include "analogReadFast.h"
#include "constants.h"
#include "joystick.h"


#define TRIGGERPIN 4
TicTacToeBoard board;
void setup(){
}

void loop(){
  board.run();
}
