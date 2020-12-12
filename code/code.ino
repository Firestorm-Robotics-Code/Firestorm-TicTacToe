#include "motor.cpp"



Motor motor(12, 11);

void setup(){
  motor.setSpeed(4000);
  motor.setGoal(32000);
}
void loop(){
  motor.run();
}
