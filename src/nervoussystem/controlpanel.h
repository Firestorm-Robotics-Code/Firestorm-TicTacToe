/* By Tyler Clarke with some help from Lawson Brashear
 * Code for the control panel, wrapped up in a class 
 * 
 * Provides an interface for joystick and button management.
 */
 
#include "analogReadFast.h"

struct ControlPanel{
  int p1Up;
  int p1Down;
  int p1Left;
  int p1Right;
  int p1Button;

  int p2Up;
  int p2Down;
  int p2Left;
  int p2Right;
  int p2Button;

  int selectorSwitch1;
  int selectorSwitch2;
  int selectorSwitch3;

  int start;
  
  ControlPanel(int p1_up, int p1_down, int p1_left, int p1_right, int p1_button, int p2_up, int p2_down, int p2_left, int p2_right, int p2_button, int selector_switch_1, int selector_switch_2, int selector_switch_3, int start_button){
    p1Up = p1_up;
    p1Down = p1_down;
    p1Left = p1_left;
    p1Rigth = p1_right;
    
    p2Up = p2_up;
    p2Down = p2_down;
    p2Left = p2_left;
    p2Right = p2_right;

    selectorSwitch1 = selector_switch_1;
    selectorSwitch2 = selector_switch_2;
    selectorSwitch3 = selector_switch_3;

    start = start_button;
  }
  void getJoystickPosition(){
    
  }
};
