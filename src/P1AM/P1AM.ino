/* By Tyler Clarke and Lawson Brashear
 * This is the main code to be uploaded to the P1AM, and is something of a pulling-it-all-together file.
 */

#include "motor.h"
/*#include "controlpanel.h"
#include "minimax.h"


#define LIMITSWITCHPIN 4
//TicTacToeBoard board;


void toggle(bool state){
  Serial.println("Toggled");
}
void pressed(){
  Serial.println("Pressed");
}
ControlPanel cp(1, 2, 3, 4, 5, &toggle, &pressed); // & (ampersand) = use pointer rather than value. This is a function pointer.
*/

Motor ymotor(12,11);
Motor xmotor(7,4);
void setup(){
  Serial.begin(115200);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  ymotor.zero(true, 3, false);
  xmotor.zero();
}

bool finLogged = false;

void loop(){
  ymotor.run();
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
    if (command.substring(0,8) == "diagonal"){
      int value = command.substring(8, command.length() - 1).toInt();
      ymotor.move(value);
      xmotor.move(value);
      finLogged = false;
    }
    if (command.substring(0,11) == "diagonalinv"){
      int value = command.substring(11, command.length() - 1).toInt();
    }
    if (command.substring(0,1) == "a"){
      ymotor.move(-ymotor.getDistance());
      xmotor.move(-xmotor.getDistance());
    }
    if (command.substring(0,6) == "speedy"){
      int value = command.substring(6, command.length() - 1).toInt();
      ymotor.setSpeed(value);
    }
    if (command.substring(0,4) == "zero"){
    }
  }
}
