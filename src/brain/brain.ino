/* By Tyler Clarke and Lawson Brashear
 * This is the main code to be uploaded to the P1AM, and is something of a pulling-it-all-together file.
 * Stepper driver configuration: on-off-on / 800 steps per rev whatever / 1.3 amps
 */

#include "motor.h"
#include "grid.h"

#define TILEWIDTH 4 // Assume 4 inches

Motor xmotor(12, 11, true, 2, true); // Y limit switch pin is 6
Motor ymotor(7, 6, true, 2, true); // X limit switch pin is 5

Grid manager(&xmotor, &ymotor, TILEWIDTH, -1); // The "-1" is the magnet pin. Set it to an invalid pin so nothing breaks if I'm stupid.

void setup(){
  Serial.begin(9600); // Begin serial at a useful bitrate
  //while (!Serial); // Wait for serial
  xmotor.setSpeed(800);
  xmotor.zero(100);
  //manager.grabPiece(true); // Get a "O"
}

bool finLogged = false;

void loop(){
  xmotor.run();
  ymotor.run();
}
