#include "motor.cpp"

#define PULPIN 12 // It turns out I was wrong: it doesn't have to be a real PWM pin. Software PWM is a thing and works.
#define DIRPIN 11

Motor motor(12, 11);

void setup(){
  motor.setSpeed(4000);
}

void loop(){
  motor.move(-10);
  motor.run();
}
