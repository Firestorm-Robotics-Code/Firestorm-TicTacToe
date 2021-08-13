// There is a trick to making sure you don't forget to code stuff. It is a simple trick, too.
// If you want to do a boolean switch, and don't know what code you'll put in the true case but want a false case (else)
// You just leave the if empty. Unfortunately, that's easy to forget.
// The solution? Put "#NOCOMPILE" in the body. It won't compile - because #NOCOMPILE is a fake directive.
// That's your lesson for today!

typedef bool boll;

#define RX 3
#define TX 4
#define JOYSTICKSPEED 6400
#include "motor.h"
#include "grid.h"
#include "lightcontrols.h"


Motor xmotor;//(2, 3, true, 12, false, 24 * 800); // Y limit switch pin is unknown
Motor ymotor(4, 5, true, 22, false, 24 * 800); // X limit switch pin is 2
Motor ymotorTwo(7, 6, true, 24, false, 24 * 800);
Grid manager(&xmotor, &ymotor, &ymotorTwo, 4 * 800   , -1        , 0, 0          , 6830, 7037              , 2465, 3172   , 19393, 15226);
//           X motor, y motor(s)         , tile width, magnet pin, x and y offset, tic-tac-toe grid x and y, O row x and y, X row x and y
// These numbers are calculated based on the CAD model. If we run into issues, redo the measurements in inches and multiply by 800 for each,
// which will be more accurate than converting from millimeters to inches via google calculator.

void setup(){ /* Setup code here. */
  manager.zero();
  manager.playPiece(false, 1, 1);
  while (!manager.isFinished());
  manager.playPiece(true, 1, 2);
  while (!manager.isFinished());
  manager.playPiece(false, 2, 1);
  while (!manager.isFinished());
  manager.playPiece(true, 1, 0);
  while (!manager.isFinished());
  manager.playPiece(false, 0, 1);
}

bool debugMode(){
  if (Serial.available()){
    String data = Serial.readString();
    if (data.substring(0,5) == "xmove"){
      xmotor.move(data.substring(6).toInt());
    }
    else if (data.substring(0, 5) == "ymove"){
      ymotor.move(data.substring(6).toInt());
    }
    else if (data.substring(0, 6) == "xspeed"){
      xmotor.setSpeed(data.substring(7).toInt());
    }
    else if (data.substring(0, 6) == "yspeed"){
      ymotor.setSpeed(data.substring(7).toInt());
    }
    else if (data.substring(0, 5) == "yzero"){
      
    }
    else if (data.substring(0, 5) == "reset"){
      
    }
  }
  return true;
}

void loop(){ /* This is the mainloop. */
  manager.run();
}
