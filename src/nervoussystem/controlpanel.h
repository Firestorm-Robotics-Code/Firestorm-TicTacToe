/* By Tyler Clarke with some help from Lawson Brashear
 * Code for the control panel, wrapped up in a class 
 * 
 * Uses a simple controlpanel protocol over serial at 9600 baud
 * 
 * First char is an opcode.
 * "0" (the alphanumeric, not the number) = button pressed.
 * "1" (same) = button released.
 * "2" (same again) = joystick state changed, read next four bytes (two 16-bit numbers, signed)
 */
 
#include "analogReadFast.h"
#define CHECK_BIT(var, pos) ((var) & 1 << (pos))


class ControlPanel{
private:

  void (*buttonToggleCallback)(bool state);
  void (*buttonPressCallback)();
  int chars2int(char char1, char char2){
    return (char1 << 8) + char2
  }

public:
  int Joystick_Y = 0;
  int Joystick_X = 0;
  bool oldbuttonstate; // Same as buttonstate, just always one update behind
  bool buttonstate; // True = pressed
  bool turn; // True = Player 1
  bool mode; // True = one player
  
  ControlPanel(void (*togglecallback)(bool state), void (*presscallback)()){ // Function callbacks. Syntax: return_type (*<name>)(<argument list>). This is for a callback function (google it) which runs whenever the button state toggles
    buttonToggleCallback = togglecallback;
    buttonPressCallback = presscallback;
    poll(); // First poll, sets the values
  }
  
  void poll(){
    if (Serial1.available()){
      char[3] message;
      Serial1.readBytes(message, 3);
    }
  }
};
