#include "motor.cpp"
#include "analogReadFast.h"
#include "constants.h"
#include "joystick.h"


#define TRIGGERPIN 4

String inches = "0";

Motor xmotor(X_PUL, X_DIR);
Motor ymotor(Y_PUL, Y_DIR);
bool directions[] = {false,false,false,false};

void setup(){
  pinMode(TRIGGERPIN,INPUT);
  motor.setSpeed(16000); // 20 inches per second. It doesn't actually go that fast (sadly) but its good enough.
  joystickSetup();
  motor.setGoal(-16000);
}

void loop(){
  joystickRead(directions);
  Serial.println(digitalRead(TRIGGERPIN));
  if (directions[0]){
    xmotor.move(1);
  }
  if (directions[1]){
    xmotor.move(-1);
  }
  if (directions[2]{
    ymotor.move(1);
  }
  if (directions[3]{
    ymotor.move(-1);
  }
  if (digitalRead(TRIGGERPIN)){
    motor.run();
  }
}
