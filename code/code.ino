#include "motor.cpp"

#include "constants.h"

#include "joystick.cpp"

String inches = "0";

Motor motor(X_PUL, X_DIR);
int[] directions = {0,0,0,0};

void setup(){
//  pinMode(TRIGGERPIN,INPUT);
  motor.setSpeed(160000); // 20 inches per second. It doesn't actually go that fast (sadly) but its good enough.
  Serial.begin(9600);
}

void loop(){
  joystickRead(*directions);
  if (Serial.available()){
    inches = Serial.readString();
    motor.move(inches.toInt() * 8000);
  }
/*  Serial.println(digitalRead(TRIGGERPIN));
  if (digitalRead(TRIGGERPIN)){
    motor.run();
  }*/
}
