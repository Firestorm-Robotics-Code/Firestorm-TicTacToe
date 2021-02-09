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
Motor xmotor(6, 7);
void setup(){
  //Serial.begin(9600);
  xmotor.setGoal(8000);
  ymotor.setGoal(800);
}

void loop(){
  ymotor.run();
  xmotor.run();
}
