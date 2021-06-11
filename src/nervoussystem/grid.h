/* By Tyler Clarke with help from Lawson Brashear
 * Wrapper around motor.h file which makes the arm move on the grid, pick up tiles, and do a variety of other tasks.
 * 
 * 5x5 grid, in gridsquares
 * 
 * Uses inches, not centimeters - multiply by 2.54
 */


#define TILEWIDTH 1 // One inch tile width for testing.
#define MAXOPS 10 // Ten is the maximum possible grid operations in cache.

class Grid{
private:
  int tilewidth;
  uint8_t grid[5][5]={ // 0 = nothing, 1 = "O", 2 = "X"
    {1,1,1,1,1},
    {0,0,0,0,2},
    {0,0,0,0,2},
    {0,0,0,0,2},
    {0,0,0,2,2}
  };
  Motor* xmotor;
  Motor* ymotor;
  int magpin;
  bool magState;
  int foundPiece[2];
  
public:
  Grid(Motor *Xmotor, Motor *Ymotor, int twidth, int magnet){
    magpin = magnet;
    xmotor = Xmotor;
    ymotor = Ymotor;
    tilewidth = twidth;
  }
  void zero(){
    xmotor -> zero(400);
    ymotor -> zero(400);
  }
  void findPiece(int *point, bool& team){
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
    xmotor -> setGoal(x * tilewidth);
    ymotor -> setGoal(y * tilewidth);
    while (!(xmotor -> isFinished() and ymotor -> isFinished())){ // Block until finished
      xmotor -> run();
      ymotor -> run();
    }
  }
  void grabPiece(bool team){ // true = "O", false = "X"
    int pos[2];
    findPiece(pos, team);
    Serial.print(pos[0]);
    Serial.print(" ");
    Serial.println(pos[1]);
    moveToGridPositionBlocking(pos[0], pos[1]);
    magnetOn();
  }
  void playPiece(int x, int y, bool team){
    grabPiece(team); // Grab a piece
    moveToGridPositionBlocking(x, y); // Move it to a position
    magnetOff(); // Drop the piece
  }
};
