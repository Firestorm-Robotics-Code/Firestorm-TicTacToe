/* By Tyler Clarke with moral support from Lawson Brashear
 * Wrapper around motor.h file which makes the arm move on the grid, pick up tiles, and do a variety of other tasks.
 * 
 * The grid it sees is actually three disjointed parts, two 5-rows of X's and O's, and a 3x3.
 * The positions (relative to start-point) can be adjusted because I finally decided I was going about it the stupidest way possible.
 * 
 * Uses inches, not centimeters - multiply by 2.54
 */


class Grid{
private:
  int tilewidth;
  uint8_t grid[3][3]={ // 0 = nothing, 1 (also False) = "O", 2 (also True) = "X".
    {0,0,0},
    {0,0,0},
    {0,0,0},
  };
  Motor* xmotor;
  Motor* ymotor;
  int magpin;
  boll magState;
  int foundPiece[2];
  int gridX; // Starting position of the grid.
  int gridY; // Ditto.

  int ORowX; // Starting position of the O row.
  int ORowY; // Ditto

  int XRowX; // Starting position of the X row.
  int XRowY; // Ditto

  int OPiecesLeft; // This is technically also the position of the first O from top.
  int XPiecesLeft; // Ditto

  uint8_t wassGood = 0; // 0 = nothing; 1 = playing a piece, going to get the piece as soon as possible; 2 = playing a piece, going to get the piece; 3 = playing a piece, got the piece;
  // 4 = resetting board, going to get a piece as soon as possible; 5 = resetting the board, going to get said piece; 6 = resetting board, got a piece and moving to fill the rack;

  unsigned int thePositionX;
  unsigned int thePositionY;
  unsigned long theRealPositionX;
  unsigned long theRealPositionY;
  bool theType; // False (0) = O, True (1) = X

  unsigned int Xoffset = 0;
  unsigned int Yoffset = 0;
  
public:
  Grid(Motor *Xmotor, Motor *Ymotor, Motor *YmotorTwo, int twidth, int magnet, int xoffset, int yoffset, int gridx, int gridy, int OsX, int OsY, int XsX, int XsY){
    magpin = magnet;
    xmotor = Xmotor;
    ymotor = Ymotor;
    ymotor -> setSlave(YmotorTwo);
    tilewidth = twidth;
    Xoffset = xoffset;
    Yoffset = yoffset;
    gridX = gridx;
    gridY = gridy;
    ORowX = OsX;
    ORowY = OsY;
    XRowX = XsX;
    XRowY = XsY;
  }
  void zero(){
    xmotor -> zero(400);
    ymotor -> zero(400);
  }
  void magnetOn(){
    digitalWrite(magpin, HIGH);
    magState = HIGH;
  }
  void magnetOff(){
    digitalWrite(magpin, LOW);
    magState = LOW;
  }
  void moveToAPiece(bool color){
    if (color){
      xmotor -> setGoal(Xoffset + XRowX);
      ymotor -> setGoal(Yoffset + XRowY + ((5 - XPiecesLeft) * tilewidth));
    }
    else{
      xmotor -> setGoal(Xoffset + ORowX + ((5 - OPiecesLeft) * tilewidth));
      ymotor -> setGoal(Yoffset + ORowY);
    }
  }
  void moveToAPosition(uint8_t x, uint8_t y){
    xmotor -> setGoal(Xoffset + gridX + (x * tilewidth));
    ymotor -> setGoal(Yoffset + gridY + (y * tilewidth));
  }
  bool findPieceOnBoard(bool type){ // Used to be two functions, now it's just one. I love c++.
    for (int y = 0; y < 2; y ++){
      for (int x = 0; x < 2; x ++){
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
      if (XPiecesLeft < 5){
        theRealPositionX = Xoffset + XRowX;
        theRealPositionY = Yoffset + XRowY + ((4 - XPiecesLeft) * tilewidth); // You might think it should be 5, not 4, but not so - it's zero indexed.
        return true;
      }
      else{
        return false;
      }
    }
    else{
      if (OPiecesLeft < 5){
        theRealPositionX = Xoffset + ORowX;
        theRealPositionY = Yoffset + ORowY + ((4 - OPiecesLeft) * tilewidth); // You might think it should be 5, not 4, but not so - it's zero indexed.
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
      if (wassGood == 1){ 
        moveToAPiece(theType);
        wassGood = 2;
        // i am a poo
        // I know you are a poo, Lawson.
      }
      else if (wassGood == 2){ // Pick up a piece
        magnetOn();
        wassGood = 3;
        moveToAPosition(thePositionX, thePositionY);
        grid[thePositionY][thePositionX] = theType + 1;
        if (theType){
          XPiecesLeft --;
        }
        else{
          OPiecesLeft ++;
        }
        delay(500);
      }
      else if (wassGood == 3){ // Drop a piece
        magnetOff();
        wassGood = 0;
        delay(500);
      }
      else if (wassGood == 4){ // We're picking up a piece.
        if (findPieceOnBoard(theType)){
          moveToAPosition(thePositionX, thePositionY);
          wassGood = 5;
        }
        else if (boardEmpty()){
          wassGood = 0;
        }
        else{
          theType = !theType; // Don't change wassGood, so it will hit here next time, but that "next time", it will measure the other type.
        }
      }
      else if (wassGood == 5){
        magnetOn();
        delay(500);
        grid[thePositionX][thePositionY] = 0;
        wassGood = 6;
        if (findEmptySlot(theType)){
          xmotor -> setGoal(theRealPositionX);
          ymotor -> setGoal(theRealPositionY);
        }
        else{
          while (!Serial);
          Serial.println("Frankly, this is embarrassing... It seems we have a bit of a bug. Just call us.");
          Serial.println("Debugging information: The issue happened in Grid::run, logic level 1-5-1, and this error log is from Grid::run, logic level 1-5-2");
          while (1);
        }
      }
      else if (wassGood == 6){
        magnetOff();
        if (!theType){ // Reverse it. Oh, how I love boolean logic...
          XPiecesLeft --;
        }
        else{
          OPiecesLeft ++;
        }
        delay(500);
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
  void reset(){
    wassGood = 4;
    theType = false;
  }
  bool isFinished(){
    return xmotor -> isFinished() && ymotor -> isFinished() && wassGood == 0; // Only in this case is it finished!
  }
};
