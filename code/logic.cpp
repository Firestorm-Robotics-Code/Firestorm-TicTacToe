#include "motor.cpp"
#include "analogReadFast.h"
#include "constants.h"
#include "joystick.h"
#define X 1
#define O 0
#define B -1
bool whoTurn = true;
bool placed = 0;
int whereX = 0;
int whereY = 0;
int board[][3]= {
  {B,B,B},
  {B,B,B},
  {B,B,B}
}
void where(){
  if (directions[0]){// makes it so when the x or y moves it makes its possiotion a 0, 1, 2, depeding apon if its in the first, second, or third possition.
    whereX = (whereX+1);
  }
  if (directions[1]){
    whereX = (whereX-1);
  }
  if (directions[2]{
    whereY = (whereY-1);
  }
  if (directions[3]{
    whereY = (whereY+1);
  }  
  while (whereX<=0){// makes sure that if an extra input is put in affter it is all the way to the right, left, up, or down the number possition will not be greater than 2 or less than 0
    whereX = (whereX+1);
  }
  while (whereY<=0){
    whereY = (whereY+1);  
  }
  while (whereX>=2){
    whereX = (whereX-1);
  }
  while (whereY>=2){
    whereY = (whereY-1);  
  }
}
void whatDoTurn(){
  if (placed == 1)
    if (whoTurn = O){
      putDown = 0;
      board[whereX][whereY]= O
      whoTurn = X;
      placed = 0;
    }else{
      putDown = 0;
      board[whereX][whereY]= X
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
