#include "motor.cpp"

#include "constants.h"

int xPinV = 0

int yPinV = 0

void readpin(){
  xPinV = analogRead(X_PIN)-512; // zero out what the pin is reading
  yPinV = analogRead(Y_PIN)-512; // same here but for y
}

void read(){
  if(yPinV >= 480 && (xPinV <= 200 && xPinV >= -200)){ // reads if the y pin's vaule is higher than 480 and if the x pin is between 200 and -200
    moveUp();
  }
  else if(yPinV <= -480 && (xPinV <= 200 && xPin >= -200)){ // reads if the y pin's vaule is lower than -480 and if the x pin is between 200 and -200
    moveDown();
  }
  else if(xPinV <= 480 && (yPinV <= 200 && yPin >= -200)){ // reads if the x pin vaule is higher that 480 and if the y pin is between 200 and -200
    moveRight();
  }
  else if(xPinV <= 480 && (yPinV <= 200 && yPin >= -200)){ // reads if the x pin vaule is lower that -480 and if the y pin is between 200 and -200
    moveLeft();
  }
}
