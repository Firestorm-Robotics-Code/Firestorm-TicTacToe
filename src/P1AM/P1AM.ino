/* By Tyler Clarke and Lawson Brashear
 * This is the main code to be uploaded to the P1AM, and is something of a pulling-it-all-together file.
 */

#include "motor.h"
#include "grid.h"

#define TILEWIDTH 4 // Assume 4 inches

Motor ymotor(12, 11, true, 6, true); // Y limit switch pin is 6
Motor xmotor(7, 4, false, 5, true); // X limit switch pin is 5

Grid manager(&xmotor, &ymotor, TILEWIDTH, -1); // The "-1" is the magnet pin. Set it to an invalid pin so nothing breaks if I'm stupid.

void setup(){
  pinMode(7, OUTPUT);
  Serial.begin(9600); // Begin serial at a useful bitrate
  //while (!Serial); // Wait for serial
  xmotor.setSpeed(800);
  xmotor.zero(800);
  //manager.grabPiece(true); // Get a "O"
}

bool finLogged = false;

void loop(){
  xmotor.run();
  if (xmotor.isFinished() && !finLogged){
    Serial.println("Finished my goal!");
    finLogged = true;
  }
  if (Serial.available()){
    String command;
    while (Serial.available()){
      command += (char)Serial.read();
    }
    if (command.substring(0,4) == "echo"){
      Serial.println(command.substring(4));
    }
    if (command.substring(0,5) == "movex"){
      int value = command.substring(5, command.length()-1).toInt();
      Serial.println(value);
      xmotor.move(value);
      finLogged = false;
    }
    if (command.substring(0,5) == "movey"){
      int value = command.substring(5, command.length() - 1).toInt();
      Serial.println(value);
      ymotor.move(value);
      finLogged = false;
    }
    if (command.substring(0,5) == "gotox"){
      int value = command.substring(5, command.length()-1).toInt();
      Serial.println(value);
      xmotor.setGoal(value);
      finLogged = false;
    }
    if (command.substring(0,5) == "gotoy"){
      int value = command.substring(5, command.length() - 1).toInt();
      Serial.println(value);
      ymotor.setGoal(value);
      finLogged = false;
    }
    if (command.substring(0,8) == "diagonal"){
      int value = command.substring(8, command.length() - 1).toInt();
      ymotor.move(value);
      xmotor.move(value);
      finLogged = false;
    }
    if (command.substring(0,11) == "diagonalinv"){
      int value = command.substring(11, command.length() - 1).toInt();
    }
    if (command.substring(0,7) == "jigglex"){
      int value = command.substring(7, command.length() - 1).toInt();
      xmotor.move(value);
      xmotor.move(-value);
    }
    if (command.substring(0,1) == "a"){
      ymotor.abort();
      xmotor.abort();
    }
    if (command.substring(0,6) == "speedy"){
      int value = command.substring(6, command.length() - 1).toInt();
      ymotor.setSpeed(value);
    }
    if (command.substring(0,4) == "zero"){
      xmotor.zero(400);
    }
  }
  ymotor.run();
  xmotor.run();
}
