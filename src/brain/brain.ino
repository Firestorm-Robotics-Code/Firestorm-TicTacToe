/* By Tyler Clarke and Lawson Brashear
 * This is the main code to be uploaded to the P1AM, and is something of a pulling-it-all-together file.
 * Stepper driver configuration: on-off-on / 800 steps per rev whatever / 1.3 amps
 */

#include "motor.h"
//#include "grid.h"
#include <SoftwareSerial.h>

#define TILEWIDTH 4 // Assume 4 inches

#define RX 4
#define TX 3

SoftwareSerial coms(RX, TX);

//Grid manager(&xmotor, &ymotor, TILEWIDTH, -1); // The "-1" is the magnet pin. Set it to an invalid pin so nothing breaks if I'm stupid.

struct funny{
  int hi;
  char d;
}; 

void setup(){
  Serial.begin(9600); // Begin serial at a useful bitrate
  //coms.begin(115200);
  //while (!coms);
  //while (!Serial); // Wait for serial
  xmotor.setSpeed(800);
  xmotor.zero(800);
  //manager.grabPiece(true); // Get a "O"
  funny data;
  data.hi = 10;
  data.d = 'z';
//  coms.write((byte*)
  xmotor.setGoal(-800);
}

bool finLogged = false;

void loop(){
  xmotor.run();
  ymotor.run();
}
