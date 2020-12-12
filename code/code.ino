#include "motor.cpp"

#include "constants.h"

String inches = "0";

Motor motor(X_PUL, X_DIR);

void setup(){
  motor.setSpeed(4000);
  Serial.begin(9600);
}
void loop(){
  if (Serial.available()){
    inches = Serial.readString();
    motor.move(inches.toInt());
  }
  motor.run();
}
