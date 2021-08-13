#include "motor.h"
#define SECONDS(x) x * 1000
#define MINUTES(x) x * SECONDS(60)
#define HOURS(x) x * MINUTES(60)
#define DAYS(x) x * HOURS(24)
Motor motor(4,6, true, -1, false);

void setup(){
  Serial.begin(9600);
  motor.setSpeed(1600);
  motor.lubricate(800, MINUTES(2), 1200, 23 * 800); // Use math because its easier. 1000 per second, 60,000 per minute, 3,600,000 per hour.
}

void loop(){
  
}
