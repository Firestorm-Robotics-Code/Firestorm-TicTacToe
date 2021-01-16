#include "motor.cpp"
#include "analogReadFast.h"
#include "constants.h"
#include "joystick.h"
#define X 1
#define O 0
#define B -1
#define JOYPINX A5
#define JOYPINY A6

class TicTacToeBoard{
private:
  bool twoPlayer = true;
  bool whoTurn = true;
  int8_t stage; // 0 = moving to space, 1 = reached space, 2 = grabbed disc, 3 = dropped disc (2&3 should revert to 0 immediately)
  bool placed = false;
  Motor ymotor(Y_PUL, Y_DIR);
  Motor xmotor(X_PUL, X_DIR);
  int8_t whereX = 0;
  int8_t whereY = 0;
  int board[][3]= {
    {B,B,B},
    {B,B,B},
    {B,B,B}
  }
  bool isTurnReady=false;
  Joystick joystick = Joystick(A5, A6);
public:
  bool zero(){
    whereX = 0;
    whereY = 0;
    return true;
  }
  void moveTo(int8_t x, int8_t y){
    // Absolute move - don't set wherex, wherey here.
    xmotor.setGoal(x*GRIDCELLSIZE);
    ymotor.setGoal(y*GRIDCELLSIZE);
  }
  void move(int8_t xm, int8_t y){
    whereX+=xm;
    whereY+=ym;
    moveTo(whereX,whereY);
  }
  void run(){
    if (isTurnReady){
      bool* directions = joystick.joystickRead();
      if (directions[0]){
        move(0,1);
      }
    }
  }
}


void whatDoTurn(){
  if (placed == 1)
    if (whoTurn = O){
      putDown = 0;
      board[whereX][whereY]= O;
      whoTurn = X;
      placed = 0;
    }else{
      putDown = 0;
      board[whereX][whereY]= X;
      whoTurn = O;
      placed = 0;
    }    
  }
}
void equals3(a, b, c) {
  return a == b && b == c && a != B;
}
void checkWinner() {
  int winner = null;

  // horizontal
  for (int i = 0; i < 3; i++) {
    if (equals3(board[i][0], board[i][1], board[i][2])) {
      winner = board[i][0];
    }
  }

  // Vertical
  for (int i = 0; i < 3; i++) {
    if (equals3(board[0][i], board[1][i], board[2][i])) {
      winner = board[0][i];
    }
  }

  // Diagonal
  if (equals3(board[0][0], board[1][1], board[2][2])) {
    winner = board[0][0];
  }
  if (equals3(board[2][0], board[1][1], board[0][2])) {
    winner = board[2][0];
  }

  int openSpots = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == B) {
        openSpots++;
      }
    }
  }

  if (winner == null && openSpots == 0) {
    return tie;
  } else {
    return winner;
  }
}
void place(){
  if(putDown == 1 && board[whereX][whereY] == B){
    placed = 1;
    placeDown();
  }  
}  
