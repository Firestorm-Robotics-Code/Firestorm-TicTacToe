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
    
    // Set oldbuttonstate to the old value of buttonstate
    
    oldbuttonstate = buttonstate;
    
    // Set Joystick X, Y
    
    Joystick_Y = analogReadFast(joystick_ypin);
    Joystick_X = analogReadFast(joystick_xpin);

    // Set new buttonstate
    
    buttonstate = digitalRead(button_pin);

    // Set who's turn value
    
    turn = digitalRead(turn_pin);

    // Set mode
    
    mode = digitalRead(mode_pin);

    // Determine if button state has toggled
    
    if (buttonstate != oldbuttonstate){
      // Check if it is a button press
      
      if // Assembly has spoiled me, so for some reason I think this looks good
      
      (buttonstate == false)
      
      { // If the button state is false (not pressed) and it is not equal to what it was, it must mean that the button has gone from false (starting state) to true (pressed) to false again, thus a click.
        buttonPressCallback(); // Run the pressed callback, this is from a function pointer (google)
      }
      
      else
      
      {
        buttonToggleCallback(&buttonstate); // Run the toggled callback, this is from a function pointer (google it)
      }
      // Actually I don't, I'm just mocking people who think having the brackets on a separate line is beautification
    }
  }
};
