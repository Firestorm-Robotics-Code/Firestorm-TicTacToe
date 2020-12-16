#include "motor.cpp"

#include "constants.h"
#include "joystick.h"

String inches = "0";

Motor motor(X_PUL, X_DIR);
bool directions[] = {false,false,false,false};

void setup(){
//  pinMode(TRIGGERPIN,INPUT);
  motor.setSpeed(160000); // 20 inches per second. It doesn't actually go that fast (sadly) but its good enough.
  Serial.begin(9600);
  joystickSetup();
}

void loop(){
  for (int i = 0; i < 4; i++) // Clear loop before getting joystick values
  {
    directions[i] = false;
  }
  joystickRead(directions);
  Serial.print(directions[0]);
  Serial.print(" ");
  Serial.print(directions[1]);
  Serial.print(" ");
  Serial.print(directions[2]);
  Serial.print(" ");
  Serial.println(directions[3]);
  if (Serial.available()){
    inches = Serial.readString();
    motor.move(inches.toInt() * 8000);
  }
  delay(1000);
/*  Serial.println(digitalRead(TRIGGERPIN));
  if (digitalRead(TRIGGERPIN)){
    motor.run();
  }*/
}
