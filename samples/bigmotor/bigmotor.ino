// Sample motor control code for the really big motor controller.

#include <AccelStepper.h> // This is an include - AccelStepper.h is an external library. You'll need to use the library manager to install it. (Google).

#define REVLEN 1600 // Revolution length
#define SPC 10 // Steps per centimeter, metric system is better bc base-10

#define PULPIN 5 // Pulse on this theoretically tells the motor to rotate one step.
#define DIRPIN 9 // Sets the direction - probably also with a pulse.

AccelStepper stepper(1, PULPIN, DIRPIN); // Create an object of the AccelStepper class, and call it stepper. The 1 specifies a two-pin control signal - direction and step.
// The PULPIN is the step pin, and DIRPIN is the direction.

void setup() {
  stepper.setMaxSpeed(1600); // Set the maximum speed for the stepper, in steps per second.
  stepper.setSpeed(1600); // Set the speed of the stepper, in steps per second. Thus, one second full rotation.
  stepper.setAcceleration(1400); // Set the acceleration speed of the stepper.
  stepper.moveTo(0); // Move to an absolute position - 0, to reset the stepper.
  stepper.runToPosition(1600); // One full rotation of the stepper - blocking.
}

void loop() {
  stepper.runSpeed(); // Run at the speed specified earlier.
}

// There are a few other commands in the stepper library, all of which are detailed in the documentation: https://www.pjrc.com/teensy/td_libs_AccelStepper.html
