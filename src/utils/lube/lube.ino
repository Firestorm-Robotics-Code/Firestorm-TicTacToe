#include "motor.h"

Motor motor(4,6, true, -1, false);

void setup(){
  Serial.begin(9600);
  motor.setSpeed(800);
  motor.lubricate(800, 14400000, 1200, 23 * 800);
  
}

void loop(){
  
}
