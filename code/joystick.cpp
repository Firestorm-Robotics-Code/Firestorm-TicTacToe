#include "motor.cpp"

#include "constants.h"

int xPinV = 0

int yPinV = 0

#define vaule 100

void readPin(){
  xPinV = analogRead(X_PIN)-512; // zero out what the pin is reading
  yPinV = analogRead(Y_PIN)-512; // same here but for y
}

void joystickRead(int *directions){
  readPin();
  if(yPinV >= 480 && (xPinV <= vaule && xPinV >= -vaule)){ // reads if the y pin's vaule is higher than 480 and if the x pin is between vaule and -vaule
    directions[0]=(true);
  }
  else if(yPinV <= -480 && (xPinV <= vaule && xPin >= -vaule)){ // reads if the y pin's vaule is lower than -480 and if the x pin is between vaule and -vaule
    directions[1]=(true);
  }
  else if(xPinV <= 480 && (yPinV <= vaule && yPin >= -vaule)){ // reads if the x pin vaule is higher that 480 and if the y pin is between vaule and -vaule
    directions[2]=(true);
  }
  else if(xPinV <= 480 && (yPinV <= vaule && yPin >= -vaule)){ // reads if the x pin vaule is lower that -480 and if the y pin is between vaule and -vaule
    directions[3]=(true);
  }
}
