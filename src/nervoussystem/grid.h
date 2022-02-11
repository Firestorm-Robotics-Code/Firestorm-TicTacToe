/* By Tyler Clarke with moral support from Lawson Brashear
 * Wrapper around motor.h file which makes the arm move on the grid, pick up tiles, and do a variety of other tasks.
 * 
 * The grid it sees is actually three disjointed parts, two 5-rows of X's and O's, and a 3x3.
 * The positions (relative to start-point) can be adjusted because I finally decided I was going about it the stupidest way possible.
 * 
 * Uses inches, not centimeters - multiply by 2.54. I hate this but we've no choice.
 */


struct Grid{
  int tilewidth;
  uint8_t grid[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  };

  Motor* xmotor;
  Motor* ymotor;
  int magpin;
  int actpin;
  boll magState;
  int foundPiece[2];
  int gridX; // Starting position of the grid.
  int gridY; // Ditto.

  int ORowX; // Starting position of the O row.
  int ORowY; // Ditto

  int XRowX; // Starting position of the X row.
  int XRowY; // Ditto

  int OPiecesLeft = 5; // This is technically also the position of the first O from top.
  int XPiecesLeft = 5; // Ditto

  uint8_t wassGood = 0; // 0 = nothing; 1 = playing a piece, going to get the piece as soon as possible; 2 = playing a piece, going to get the piece; 3 = playing a piece, got the piece;
  // 4 = resetting board, going to get a piece as soon as possible; 5 = resetting the board, going to get said piece; 6 = resetting board, got a piece and moving to fill the rack;

  uint8_t thePositionX;
  uint8_t thePositionY;
  unsigned long theRealPositionX;
  unsigned long theRealPositionY;
  bool theType; // False (0) = O, True (1) = X

  unsigned int Xoffset = 0;
  unsigned int Yoffset = 0;

  void (*finishedCallback)();
  bool hasFinishedCallback = false;
  void (*pieceMovedCallback)();
  boll hasPieceMovedCallback = false;
  void (*pieceGrabbedCallback)();
  boll hasPieceGrabbedCallback = false;
  void (*piecePlayedCallback)();
  boll hasPiecePlayedCallback = false;
  
public:
  Grid(Motor *Xmotor, Motor *Ymotor, Motor *YmotorTwo, int twidth, int magnet, int actuator, int xoffset, int yoffset, int gridx, int gridy, int OsX, int OsY, int XsX, int XsY){
    magpin = magnet;
    pinMode(magpin, OUTPUT);
    actpin = actuator;
    pinMode(actpin, OUTPUT);
    xmotor = Xmotor;
    ymotor = Ymotor;
    tilewidth = twidth;
    ymotor -> setSlave(YmotorTwo);
    Xoffset = xoffset;
    Yoffset = yoffset;
    gridX = gridx;
    gridY = gridy;
    ORowX = OsX;
    ORowY = OsY;
    XRowX = XsX;
    XRowY = XsY;
  }
  
  void setFinishedCallback(void (*newCallback)()){
    finishedCallback = newCallback;
    hasFinishedCallback = true;
  }
  void setPieceMovedCallback(void (*newCallback)()){
    pieceMovedCallback = newCallback;
    hasPieceMovedCallback = true;
  }
  void setPieceGrabbedCallback(void (*newCallback)()){
    pieceGrabbedCallback = newCallback;
    hasPieceGrabbedCallback = true;
  }
  void setPiecePlayedCallback(void (*newCallback)()){
    piecePlayedCallback = newCallback;
    hasPiecePlayedCallback = true;
  }
  void zero(){
    xmotor -> zero(400);
    ymotor -> zero(400);
  }
  void cheat(bool turn){
    moveToAPiece(turn);
    magnetOn();
    if (findEmptySlot(theType)){
      xmotor -> setGoal(theRealPositionX);
      ymotor -> setGoal(theRealPositionY);
    }
    runUntilFinished();
    magnetOff();
    /*if (theType){ // Reverse it. Oh, how I love boolean logic...
      XPiecesLeft ++;
    }
    else{
      OPiecesLeft ++;
    }*/
  }
  void setSpeed(int speed){
    ymotor -> setSpeed(speed);
    xmotor -> setSpeed(speed);
  }
  void magnetOn(){
    digitalWrite(actpin, HIGH);
    digitalWrite(magpin, HIGH);
    magState = HIGH;
    delay(1000);
    digitalWrite(actpin, LOW);
    delay(250);
  }
  void magnetOff(){
    digitalWrite(actpin, HIGH);
    digitalWrite(magpin, LOW);
    magState = LOW;
    delay(1000);
    digitalWrite(actpin, LOW);
    delay(250);
  }
  void moveToAPiece(bool color){
    if (color){
      xmotor -> setGoal(Xoffset + XRowX);
      ymotor -> setGoal(Yoffset + XRowY + ((XPiecesLeft - 1) * tilewidth));
      if (XPiecesLeft < 0 || XPiecesLeft > 5){
        while (!Serial);
        Serial.println("SOFTWARE FAULT - The number of pieces left is irrational. This issue CANNOT be resolved by any other than Tyler Clarke. Fault location: grid.h::Grid::moveToAPiece::if.1::if.1");
        while (1);
      }
    }
    else{
      xmotor -> setGoal(Xoffset + ORowX);
      ymotor -> setGoal(Yoffset + ORowY + ((OPiecesLeft - 1) * tilewidth));
      if (OPiecesLeft < 0 || OPiecesLeft > 5){
        while (!Serial);
        Serial.println("SOFTWARE FAULT - The number of pieces left is irrational. This issue CANNOT be resolved by any other than Tyler Clarke. Fault location: grid.h::Grid::moveToAPiece::else.1::if.1");
        while (1);
      }
    }
  }
  void moveToAPosition(uint8_t x, uint8_t y){
    xmotor -> setGoal(Xoffset + gridX + (x * tilewidth));
    ymotor -> setGoal(Yoffset + gridY + (y * tilewidth));
  }
  bool findPieceOnBoard(bool type){ // Used to be two functions, now it's just one. I love c++.
    for (int y = 0; y < 3; y ++){
      for (int x = 0; x < 3; x ++){
        if (grid[y][x] - 1 == type){ // If it is there, return true. Otherwise, return false.
          // This potentially saves space and time, space because I would often allocate another "returner" variable, and time because it doesn't have to iterate all the way through.
          thePositionX = x;
          thePositionY = y;
          return true;
        }
      }
    }
    return false;
  }
  bool findEmptySlot(bool type){
    if (type){
      if (XPiecesLeft < 6){
        theRealPositionX = Xoffset + XRowX;
        theRealPositionY = Yoffset + XRowY + ((XPiecesLeft - 1) * tilewidth);
        return true;
      }
      else{
        return false;
      }
    }
    else{
      if (OPiecesLeft < 6){
        theRealPositionX = Xoffset + ORowX;
        theRealPositionY = Yoffset + ORowY + ((OPiecesLeft - 1) * tilewidth);
        return true;
      }
      else{
        return false;
      }
    }
  }
  bool boardEmpty(){
    return (grid[0][0] + grid[0][1] + grid[0][2] +
           grid[1][0] + grid[1][1] + grid[1][2] +
           grid[2][0] + grid[2][1] + grid[2][2]) == 0;
  }
  void run(){
    if (ymotor -> isFinished() && xmotor -> isFinished()){
      if (hasFinishedCallback){
        finishedCallback();
      }
      if (wassGood == 1){ 
        moveToAPiece(theType);
        wassGood = 2;
        // i am a poo
        // I know you are a poo, Lawson.
      }
      else if (wassGood == 2){ // Pick up a piece
        if (hasPieceGrabbedCallback){
          pieceGrabbedCallback();
        }
        magnetOn();
        wassGood = 3;
        moveToAPosition(thePositionX, thePositionY);
        if (theType){
          XPiecesLeft --;
        }
        else{
          OPiecesLeft --;
        }
      }
      else if (wassGood == 3){ // Drop a piece
        if (hasPieceMovedCallback){
          pieceMovedCallback();
        }
        grid[thePositionY][thePositionX] = theType + 1;
        magnetOff();
        wassGood = 0;
      }
      else if (wassGood == 4){ // We're picking up a piece.
        if (findPieceOnBoard(theType)){
          moveToAPosition(thePositionX, thePositionY);
          wassGood = 5;
        }
        else if (boardEmpty()){
          moveToAPosition(0, 0);
          wassGood = 0;
        }
        else{
          theType = !theType; // Don't change wassGood, so it will hit here next time, but that "next time", it will measure the other type.
        }
      }
      else if (wassGood == 5){
        magnetOn();
        grid[thePositionY][thePositionX] = 0; // This is one of those buggies - it was once `grid[thePositionX][thePositionY]`!
        if (theType){ // Reverse it. Oh, how I love boolean logic...
          XPiecesLeft ++;
        }
        else{
          OPiecesLeft ++;
        }
        if (hasPieceGrabbedCallback){
          pieceGrabbedCallback();
        }
        wassGood = 6;
        if (findEmptySlot(theType)){
          xmotor -> setGoal(theRealPositionX);
          ymotor -> setGoal(theRealPositionY);
        }
        else{
          while (!Serial);
          Serial.println("SOFTWARE FAULT - findEmptySlot returned false. This error was reported in grid.h::Grid::run.");
          while (1);
        }
      }
      else if (wassGood == 6){
        magnetOff();
        if (hasPieceMovedCallback){
          pieceMovedCallback();
        }
        wassGood = 4;
      }
    }
    ymotor -> run();
    xmotor -> run();
  }
  void playPiece(bool type, int x, int y){
    wassGood = 1;
    theType = type;
    thePositionX = x;
    thePositionY = y;
  }
  bool positionOccupied(int x, int y){
    return !(grid[y][x] == 0);
  }
  void reset(){
    wassGood = 4;
    theType = false;
  }
  bool isFinished(){
    return xmotor -> isFinished() && ymotor -> isFinished() && wassGood == 0; // Only in this case is it finished!
    // Stepping through it:
    // xmotor -> isFinished() && ymotor -> isFinished() checks the motors
    // wassGood == 0 makes sure it is finished with whatever task it is doing
  }
  bool equals3(uint8_t a, uint8_t b, uint8_t c){
    return a == b && b == c && c != 0;
  }
  bool boardFilled(){
    for (int y = 0; y < 3; y ++){
      for (int x = 0; x < 3; x ++){
        if (grid[y][x] == 0){
          return false; // Logical exclusion. If any tile is NOT filled, we return false!
        }
      }
    }
    return true; // And then if it never returns false, it makes it here and returns true!
  }
  void runUntilFinished(){
    while (!isFinished()){
      run();
    }
  }
  uint8_t checkWinner(uint8_t *firstpos, uint8_t *secondpos){ // If you have a bug, its probably in here!
    for (int i = 0; i < 3; i ++){
      if (grid[i][0] != 0 && equals3(grid[i][0], grid[i][1], grid[i][2])){
        firstpos[0] = 0;
        firstpos[1] = i;
        secondpos[0] = 2;
        secondpos[1] = i;
        return 2;
      }
      else if (grid[0][i] != 0 && equals3(grid[0][i], grid[1][i], grid[2][i])){
        firstpos[0] = i;
        firstpos[1] = 0;
        secondpos[0] = i;
        secondpos[1] = 2;
        return 2;
      }
    }
    if (grid[0][0] != 0 && equals3(grid[0][0], grid[1][1], grid[2][2])){
      firstpos[0] = 0;
      firstpos[1] = 0;
      secondpos[0] = 2;
      secondpos[1] = 2;
      return 2;
    }
    if (grid[2][0] != 0 && equals3(grid[0][2], grid[1][1], grid[2][0])){
      firstpos[0] = 2;
      firstpos[1] = 0;
      secondpos[0] = 0;
      secondpos[1] = 2;
      return 2;
    }
    if (boardFilled()){
      return 1;
    }
    return 0;
  }
  void cancel(){ // Cancels every operation.
    while (!(wassGood == 0 || wassGood == 1 || wassGood == 4)){
      run();
    }
    reset();
    runUntilFinished();
  }
};
