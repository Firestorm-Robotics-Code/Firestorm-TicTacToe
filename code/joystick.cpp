#include "motor.cpp"

#include "constants.h"

int xPinV = 0

int yPinV = 0

void setup(){
  xPinV = analogRead(X_PIN)-512;
  yPinV = analogRead(Y_PIN)-512;
}

void loop(){
  if(yPinV >= 480 && (xPinV <= 200 && xPinV >= -200)){
    motor.move(UP);
  }
  else if(yPinV <= -480 && (xPinV <= 200 && xPin >= -200)){
    motor.move(DOWN);
  }
}
