// Receives commands over serial.
// Uses a bit-banged protocol with object-over-serial.
// Commands for sending: serialobject.write((bytes*)object, sizeof(object));
// Commands for receiving: type data = (type)serialobject.readBytes(sizeof(type));
typedef bool boll;

#define RX 3
#define TX 4
#define JOYSTICKSPEED 6400
#include "motor.h"
#include "grid.h"
#include "lightcontrols.h"
//#include <SoftwareSerial.h>

struct funny{
  int hi;
  char d;
}; 

//SoftwareSerial coms(RX, TX);
Motor xmotor;//(2, 3, true, 12, false, 24 * 800); // Y limit switch pin is unknown
Motor ymotor(4, 5, true, 22, false, 24 * 800); // X limit switch pin is 2
Motor ymotorTwo(7, 6, true, 24, false, 24 * 800);
Grid manager(&xmotor, &ymotor, 4 * 800, -1, 2000, 2000); // 4 inch squares, 2.5 inch offset

void setup(){ /* Setup code here. */
  //pinMode(8, INPUT_PULLUP);
  //pinMode(9, INPUT_PULLUP);
  //pinMode(10, INPUT_PULLUP);
  //pinMode(11, INPUT_PULLUP);
  Serial.begin(9600);
  //manager.zero();
  ymotor.lubricate(800, 1000, 400, 23 * 800);
  ymotorTwo.lubricate(800, 1000, 400, 23 * 800);
  xmotor.setSpeed(1600);
  ymotor.setSpeed(3200);
  ymotorTwo.setSpeed(3200);
  ymotor.zeroTwo(800, &ymotorTwo);

  bool voop = true;

  ymotor.move(8000);
  //xmotor.move(800);

  /*manager.playPiece(0,0,false);
  delay(2000);
  manager.playPiece(1,1,true);
  delay(2000);
  manager.playPiece(0,1,false);
  delay(2000);
  manager.playPiece(1, 2, true);
  delay(2000);
  manager.playPiece(0, 2, false);
  Serial.println("O wins");*/
}

bool debugMode(){
  if (Serial.available()){
    String data = Serial.readString();
    Serial.println(data.substring(0,5));
    if (data.substring(0,5) == "xmove"){
      Serial.println("Yup");
      xmotor.move(data.substring(6).toInt());
    }
    else if (data.substring(0, 5) == "ymove"){
      Serial.println("Yup");
      ymotor.move(data.substring(6).toInt());
    }
    else if (data.substring(0, 6) == "xspeed"){
      xmotor.setSpeed(data.substring(7).toInt());
    }
    else if (data.substring(0, 6) == "yspeed"){
      ymotor.setSpeed(data.substring(7).toInt());
    }
    else if (data.substring(0, 5) == "yzero"){
      ymotor.zeroTwo(400, ymotorTwo);
    }
    else if (data.substring(0, 5) == "reset"){
      
    }
  }
  return true;
}

void loop(){ /* This is the mainloop. */
  ymotor.run();
  xmotor.run();
  if (Serial.available()){
    lights::chant(<This won't compile, as it is a standin for a HardwareSerial>, 4); // Enter debug mode!
    while (debugMode);
  }
}
