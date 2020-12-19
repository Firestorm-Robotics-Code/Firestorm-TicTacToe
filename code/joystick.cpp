#include <Arduino.h>
#include "analogReadFast.h"

int xPinV = 0;

int yPinV = 0;

#define X_PIN A5

#define Y_PIN A6

#define WINDOW 200 // 200 point window for any direction
#define BREAKINGPOINT 450 // The value of the joystick must be at least this, or the direction is not read. 450 was hardcoded before 4 times, so this replaces it.

void joystickSetup(){
  pinMode(X_PIN,INPUT);
  pinMode(Y_PIN,INPUT);
}

void joystickRead(bool directions[4]){
  xPinV = analogReadFast(X_PIN)-512; // zero out what the pin is reading
  yPinV = analogReadFast(Y_PIN)-512; // same here but for y
  if(yPinV >= BREAKINGPOINT && (xPinV <= WINDOW && xPinV >= -WINDOW)){ // reads if the y pin's value is higher than BREAKINGPOINT and if the x pin is between WINDOW and -WINDOW
    directions[0]=true;
  }
  else{
    directions[0]=false;
  }
  if(yPinV <= -BREAKINGPOINT && (xPinV <= WINDOW && xPinV >= -WINDOW)){ // Same, but for the y pin lower than -BREAKINGPOINT rather than higher
    directions[1]=true;
  }
  else{
    directions[1]=false;
  }
  if(xPinV >= BREAKINGPOINT && (yPinV <= WINDOW && yPinV >= -WINDOW)){ // Same as the first one, except the axes are flipped
    directions[2]=true;
  }
  else{
    directions[2]=false;
  }
  if(xPinV <= -BREAKINGPOINT && (yPinV <= WINDOW && yPinV >= -WINDOW)){ // Same as above, just less than -BREAKINGPOINT rather than greater than 450
    directions[3]=true;
  }
  else{
    directions[3]=false;
  }
}
