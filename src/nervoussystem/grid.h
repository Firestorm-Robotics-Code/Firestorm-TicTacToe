/* By Tyler Clarke with help from Lawson Brashear
 * Wrapper around motor.h file which makes the arm move on the grid, pick up tiles, and do a variety of other tasks.
 * 
 * 5x5 grid, in gridsquares
 * 
 * Uses inches, not centimeters - multiply by 2.54
 */


#define MAXOPS 10 // Ten is the maximum possible grid operations in cache.

class Grid{
private:
  int tilewidth;
  uint8_t grid[5][5]={ // 0 = nothing, 1 (also False) = "O", 2 (also True) = "X". Note that it is rotated 90 degrees clockwise.
    {1,1,1,1,1},
    {0,0,0,0,2},
    {0,0,0,0,2},
    {0,0,0,0,2},
    {0,0,0,2,2}
  };
  Motor* xmotor;
  Motor* ymotor;
  int magpin;
  boll magState;
  int foundPiece[2];
  int Xoffset;
  int Yoffset;
  
public:
  Grid(Motor *Xmotor, Motor *Ymotor, int twidth, int magnet, int xoffset, int yoffset){
    magpin = magnet;
    xmotor = Xmotor;
    ymotor = Ymotor;
    tilewidth = twidth;
    Xoffset = xoffset;
    Yoffset = yoffset;
  }
  void zero(){
    xmotor -> zero(400);
    ymotor -> zero(400);
    xmotor -> move(Xoffset);
    ymotor -> move(Yoffset);
  }
  void findPiece(int *point, bool team){
    for (int i = 0; i < 5; i++){
      if (grid[0][i] == team + 1){
        point[0] = 0;
        point[1] = i;
        return;
      }
    }
    for (int i = 0; i < 5; i++){
      if (grid[i][4] == team + 1){
        point[0] = i;
        point[1] = 4;
        return;
      }
    }
    if (grid[3][4] == team + 1){
      point[0] = 3;
      point[1] = 4;
      return;
    }
    point[0] = -1;
    point[1] = -1;
  }
  void magnetOn(){
    magState = true; // This is for testing without a magnet. Just delete the comment marks on the below line (and the equivalent in magnetOff) to work a magnet.
    //digitalWrite(magPin, HIGH);
  }
  void magnetOff(){
    magState = false;
    //digitalWrite(magPin, LOW);
  }
  void moveToGridPositionBlocking(int x, int y){
    Serial.println("Yo!");
    xmotor -> setGoal(x * tilewidth + Xoffset);
    ymotor -> setGoal(y * tilewidth + Yoffset);
    Serial.println("Ferp");
    while (!(xmotor -> isFinished() && ymotor -> isFinished())){ // Block until finished
      xmotor -> run();
      ymotor -> run();
    }
    Serial.println("Stoop");
  }
  void grabPiece(bool team, int delayFish = 0){ // true = "O", false = "X"
    int pos[2];
    findPiece(pos, team);
    moveToGridPositionBlocking(pos[0], pos[1]);
    magnetOn();
    delay(delayFish);
    grid[pos[0]][pos[1]] = 0;
  }
  void playPiece(int x, int y, bool team, int delayFish=500){
    grabPiece(team, delayFish); // Grab a piece
    Serial.println("Pieces grabbed");
    moveToGridPositionBlocking(x + 1, y + 1); // Move it to a position - The "x + 1, y + 1" is because this is a five-tile grid and its supposed to place in a three-tile segment
    Serial.println("Moved!");
    magnetOff(); // Drop the piece
    grid[x + 1][y + 1] = team + 1;
  }
};
