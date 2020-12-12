#include <Arduino.h>

int xPinV = 0;

int yPinV = 0;

#define X_PIN A5

#define Y_PIN A6

#define vaule 200

void readPin(){
  xPinV = analogRead(X_PIN)-512; // zero out what the pin is reading
  yPinV = analogRead(Y_PIN)-512; // same here but for y
}

void joystickRead(bool directions[4]){
  readPin();
  if(yPinV >= 450 && (xPinV <= vaule && xPinV >= -vaule)){ // reads if the y pin's vaule is higher than 450 and if the x pin is between vaule and -vaule
    directions[0]=true;
  }
  else if(yPinV <= -450 && (xPinV <= vaule && xPinV >= -vaule)){ // reads if the y pin's vaule is lower than -450 and if the x pin is between vaule and -vaule
    directions[1]=true;
  }
  else if(xPinV <= 450 && (yPinV <= vaule && yPinV >= -vaule)){ // reads if the x pin vaule is higher that 450 and if the y pin is between vaule and -vaule
    directions[2]=true;
  }
  else if(xPinV <= -450 && (yPinV <= vaule && yPinV >= -vaule)){ // reads if the x pin vaule is lower that -450 and if the y pin is between vaule and -vaule
    directions[3]=true;
  }
}
