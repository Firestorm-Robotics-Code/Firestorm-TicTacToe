#include "motor.cpp"

#include "constants.h"

String inches = "0";

Motor motor(X_PUL, X_DIR);

void setup(){
  motor.setSpeed(160000); // 20 inches per second. It doesn't actually go that fast (sadly) but its good enough.
  Serial.begin(9600);
}
void loop(){
  if (Serial.available()){
    inches = Serial.readString();
    motor.move(inches.toInt() * 8000);
  }
  motor.run();
}
