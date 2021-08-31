/* By Tyler Clarke with some help from Lawson Brashear
 * Code for the control panel, wrapped up in a class 
 * 
 * Provides interfaces for joystick and button management.
 */

struct FourJoystick{ // This thing controls a 4-button joystick. Same as an NES joystick.
public:
  int upButton;
  bool upButtonPressed;
  bool upButtonReleased;
  
  int downButton;
  bool downButtonPressed;
  bool downButtonReleased;
  
  int leftButton;
  bool leftButtonPressed;
  bool leftButtonReleased;
  
  int rightButton;
  bool rightButtonPressed;
  bool rightButtonReleased;

  int xChange;
  int yChange;
  
  FourJoystick(int up, int down, int left, int right){
    upButton = up;
    pinMode(upButton, INPUT_PULLUP);
    downButton = down;
    pinMode(downButton, INPUT_PULLUP);
    leftButton = left;
    pinMode(leftButton, INPUT_PULLUP);
    rightButton = right;
    pinMode(rightButton, INPUT_PULLUP);
  }

  void poll(){
    bool oldUp = upButtonPressed;
    upButtonPressed = !digitalRead(upButton);
    bool oldDown = downButtonPressed;
    downButtonPressed = !digitalRead(downButton);
    bool oldLeft = leftButtonPressed;
    leftButtonPressed = !digitalRead(leftButton);
    bool oldRight = rightButtonPressed;
    rightButtonPressed = !digitalRead(rightButton);
    if (oldUp && !upButtonPressed){
      upButtonReleased = true;
      yChange += 1;
    }
    if (oldDown && !downButtonPressed){
      downButtonReleased = true;
      yChange -= 1;
    }
    if (oldLeft && !leftButtonPressed){
      leftButtonReleased = true;
      xChange -= 1;
    }
    if (oldRight && !rightButtonPressed){
      rightButtonReleased = true;
      xChange += 1;
    }
  }

  bool upPressed(){ // Returns if the up button was pressed at last poll.
    bool spoon = upButtonPressed;
    upButtonPressed = false;
    return spoon;
  }

  bool upReleased(){ // Returns if the up button was pressed at last poll.
    bool spoon = upButtonReleased;
    upButtonReleased = false;
    return spoon;
  }

  bool downPressed(){ // Same but for the down button
    bool spoon = downButtonPressed;
    downButtonPressed = false;
    return spoon;
  }

  bool downReleased(){ // Same but for the down button
    bool spoon = downButtonReleased;
    downButtonReleased = false;
    return spoon;
  }

  bool leftPressed(){ // Ditto on the left one
    bool spoon = leftButtonPressed;
    leftButtonPressed = false;
    return spoon;
  }

  bool leftReleased(){ // Ditto on the left one
    bool spoon = leftButtonReleased;
    leftButtonReleased = false;
    return spoon;
  }

  bool rightPressed(){ // Right one
    bool spoon = rightButtonPressed;
    rightButtonPressed = false;
    return spoon;
  }

  bool rightReleased(){ // Right one
    bool spoon = rightButtonReleased;
    rightButtonReleased = false;
    return spoon;
  }

  uint8_t getXChange(){
    uint8_t spoon = xChange;
    xChange = 0;
    return spoon;
  }

  uint8_t getYChange(){
    uint8_t spoon = yChange;
    yChange = 0;
    return spoon;
  }
};

struct ThreeSelectorSwitch{
  uint8_t typeOnePin;
  uint8_t typeThreePin;
  uint8_t position = 0;
  ThreeSelectorSwitch(uint8_t one, uint8_t three){ // Note that the pullups must be logically flipped, as closed is a one and open is a zero.
    typeOnePin = one;
    pinMode(one, INPUT_PULLUP);
    typeThreePin = three;
    pinMode(three, INPUT_PULLUP);
  }
  void poll(){
    if (!digitalRead(typeOnePin)){
      position = 0;
    }
    else if (!digitalRead(typeThreePin)){
      position = 2;
    }
    else{
      position = 1;
    }
  }
};

struct PushButton{
  int thePin;
  bool buttonPushed;
  bool buttonReleased;
  PushButton(int pin){
    thePin = pin;
    pinMode(pin, INPUT_PULLUP);
  }
  void poll(){
    if (!digitalRead(thePin)){
      buttonPushed = true;
    }
    else{
      if (buttonPushed){
        buttonReleased = true;
      }
      buttonPushed = false;
    }
  }
  bool wasButtonPushed(){
    bool spoon = buttonPushed;
    buttonPushed = false;
    return spoon;
  }
  bool wasButtonReleased(){
    bool spoon = buttonReleased;
    buttonReleased = false;
    return spoon;
  }
};
