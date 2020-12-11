#include "motor.cpp"

Motor motor(11, 12);

void setup(){
  motor.setGoal(8000);
}

void loop(){
  motor.run();
}
