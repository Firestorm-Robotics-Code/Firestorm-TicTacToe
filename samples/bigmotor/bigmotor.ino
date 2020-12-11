// Sample motor control code for the really big motor controller.

#include <AccelStepper.h> // This is an include - AccelStepper.h is an external library. You'll need to use the library manager to install it. (Google).

#define REVLEN 8000 // Revolution length. We have SW5 on, so its actually 12800 - but I'll need to talk to Andrew Cua about that one.

#define PULPIN 11 // Pulse on this theoretically tells the motor to rotate one step.
#define DIRPIN 12 // Sets the direction.

AccelStepper stepper(1, PULPIN, DIRPIN); // Create an object of the AccelStepper class, and call it stepper. The 1 specifies a two-pin control signal - direction and step.
// The PULPIN is the step pin, and DIRPIN is the direction.

void moveInches(AccelStepper *stepperdoo, double inches){
  Serial.print("E Goner");
  stepperdoo->move(REVLEN * inches); // One inch per revolution, one revolution per REVLEN steps
  Serial.print("Yo!");
  // "->" is like "." if your using a pointer, which we are for code cleanliness.
}

void setup() {
  stepper.setMaxSpeed(10*REVLEN); // Max speed ten revolutions per second
  stepper.setSpeed(REVLEN); // One revolution per second, bc one revolution per REVLEN steps
  //stepper.move(8000);
  //moveInches(&stepper, 1); // &stepper passes a pointer, rather than a value. It probably doesn't matter, but I'm trying to save on space.
}

void loop() {
  stepper.runSpeed();//ToPosition(); // Run at the speed specified earlier.
}

// There are a few other commands in the stepper library, all of which are detailed in the documentation: https://www.pjrc.com/teensy/td_libs_AccelStepper.html
