// Receives commands over serial.
// Uses a bit-banged protocol with object-over-serial.
// Commands for sending: serialobject.write((bytes*)object, sizeof(object));
// Commands for receiving: type data = (type)serialobject.readBytes(sizeof(type));

#define RX 3
#define TX 4
#define JOYSTICKSPEED 6400
#include "motor.h"
//#include <SoftwareSerial.h>

struct funny{
  int hi;
  char d;
}; 

//SoftwareSerial coms(RX, TX);
Motor xmotor(12, 11, true, 2, false, 24 * 800); // Y limit switch pin is unknown
Motor ymotor(7, 4, true, 5, true, 24 * 800); // X limit switch pin is 2

void setup(){ /* Setup code here. */
  //pinMode(8, INPUT_PULLUP);
  //pinMode(9, INPUT_PULLUP);
  //pinMode(10, INPUT_PULLUP);
  //pinMode(11, INPUT_PULLUP);
  Serial.begin(9600);
  while (!Serial); // Wait for serial connection. I know this is annoying but... Ok, I don't know this is annoying. Random fact: Precompiler macros are nearly turing-complete.
  Serial.println("Let the Games Begin");
  xmotor.setSpeed(800);
  ymotor.setSpeed(800);
  ymotor.zero(400);
}

void loop(){ /* This is the mainloop. */
  /*if (!digitalRead(8)){
    ymotor.run(-JOYSTICKSPEED);
  }
  else if (!digitalRead(10)){
    ymotor.run(JOYSTICKSPEED);
  }
  else{
    ymotor.run();
  }
  if (!digitalRead(9)){
    xmotor.run(JOYSTICKSPEED);
  }
  else if (!digitalRead(11)){
    xmotor.run(-JOYSTICKSPEED);
  }
  else{
    xmotor.run();
  }*/
  ymotor.run();
  xmotor.run();
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
      ymotor.zero(400);
    }
  }
}
