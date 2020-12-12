#include "motor.cpp"

#include "constants.h"

String inches = "0";

Motor motor(X_PUL, X_DIR);

void setup(){
  pinMode(TRIGGERPIN,INPUT);
  motor.setSpeed(1600); // 20 inches per second. It doesn't actually go that fast (sadly) but its good enough.
  Serial.begin(9600);
}

void moveUp(){
  Serial.println("Up");
}
void moveDown(){
  Serial.println("Down");
}
void moveLeft(){
  Serial.println("Left");
}
void moveRight(){
  Serial.println("Right");
}

void loop(){
  if (Serial.available()){
    inches = Serial.readString();
    motor.move(inches.toInt() * 8000);
  }
  Serial.println(digitalRead(TRIGGERPIN));
  if (digitalRead(TRIGGERPIN)){
    motor.run();
  }
}
