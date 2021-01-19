#include "analogReadFast.h"


class ControlPanel{
private:
  int joystick_ypin;
  int joystick_xpin;
  int button_pin;
  int turn_pin;
  int mode_pin;
  
  void (*buttonToggleCallback)(bool state);
  void (*buttonPressCallback)();

public:
  int Joystick_Y = 0;
  int Joystick_X = 0;
  bool oldbuttonstate; // Same as buttonstate, just always one update behind
  bool buttonstate; // True = pressed
  bool turn; // True = Player 1
  bool mode; // True = one player
  
  ControlPanel(int xpin, int ypin, int buttonpin, int turnpin, int modepin, void (*togglecallback)(bool state), void (*presscallback)()){ // Function callbacks. Syntax: return_type (*<name>)(<argument list>). This is for a callback function (google it) which runs whenever the button state toggles
    ypin = ypin;
    xpin = xpin;
    button_pin = buttonpin;
    turn_pin = turnpin;
    mode_pin = modepin;
    buttonToggleCallback = togglecallback;
    buttonPressCallback = presscallback;
    poll(); // First poll, sets the values
  }
  
  void poll(){
    oldbuttonstate = buttonstate;
    Joystick_Y = analogReadFast(joystick_ypin);
    Joystick_X = analogReadFast(joystick_xpin);
    buttonstate = digitalRead(button_pin);
    turn = digitalRead(turn_pin);
    mode = digitalRead(mode_pin);
    if (buttonstate != oldbuttonstate){
      buttonToggleCallback(&buttonstate);
      if (buttonstate == false){ // If the button state is false (not pressed) and it is not equal to what it was, it must mean that the button has gone from false (starting state) to true (pressed) to false again, thus a click.
        buttonPressCallback();
      }
    }
  }
};
