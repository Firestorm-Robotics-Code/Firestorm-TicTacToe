/* By Tyler Clarke
 *  
 *  Classes for game management. Makes it more organized.
 *  
 *  Simple game workflow:
 *  Create object "game" of the TwoPlayerGame class
 *  In void loop, do:
if (game.playing){
  game.run();
}
 */
//#include "minimax.h"
 
struct Game{
  Grid *manager;
  bool playing = false;

  NeoPixelController ringLight{12, 22};

  bool turn = true;
  uint8_t headX = 0;
  uint8_t headY = 0;

  bool oldTurn = true;

  Game(Grid *management){
    manager = management;
  }
  
  void run(){
    if (headX == 3){ // One more than two
      headX = 2;
    }
    if (headX > 3){ // Unsigned integer, so one under 0 = 255 or 256
      headX = 0;
    } // Duck if I ever think about the number of times I have re-written this code
    if (headY == 3){ // One over 2
      headY = 2;
    }
    if (headY > 3){ // Unsigned integer, so one under 0 = 255 or 256
      headY = 0;
    }
    if (manager -> isFinished()){
      doWinnerStuff();
    }
    if (turn != oldTurn){
      if (!turn){
        ringLight.swirly(255, 0, 0, 125);
      }
      else{
        ringLight.swirly(0, 0, 255, 125);
      }
      oldTurn = turn;
    }
  }
  
  void newGame(){
    playing = true;
    if (!turn){
      ringLight.swirly(255, 0, 0, 125);
    }
    else{
      ringLight.swirly(0, 0, 255, 125);
    }
  }

  void danceTie(){
    ringLight.setAsOneColor(255, 255, 255);
    ringLight.pixels -> show();
    delay(500);
    ringLight.pixels -> clear();
    ringLight.pixels -> show();
    delay(500);
    ringLight.setAsOneColor(255, 255, 255);
    ringLight.pixels -> show();
    delay(500);
    ringLight.pixels -> clear();
    ringLight.pixels -> show();
    delay(500);
    ringLight.setAsOneColor(255, 255, 255);
    ringLight.pixels -> show();
    delay(500);
    ringLight.pixels -> clear();
    ringLight.pixels -> show();
    delay(500);
  }
  
  void danceWin(int x1, int y1, int x2, int y2){
    if (!turn){
      ringLight.setAsOneColor(255, 0, 0);
      ringLight.pixels -> show();
      delay(500);
      ringLight.pixels -> clear();
      ringLight.pixels -> show();
      delay(500);
      ringLight.setAsOneColor(255, 0, 0);
      ringLight.pixels -> show();
      delay(500);
      ringLight.pixels -> clear();
      ringLight.pixels -> show();
      delay(500);
      ringLight.setAsOneColor(255, 0, 0);
      ringLight.pixels -> show();
      delay(500);
      ringLight.pixels -> clear();
      ringLight.pixels -> show();
      delay(500);
    }
    else{
      ringLight.setAsOneColor(0, 0, 255);
      ringLight.pixels -> show();
      delay(500);
      ringLight.pixels -> clear();
      ringLight.pixels -> show();
      delay(500);
      ringLight.setAsOneColor(0, 0, 255);
      ringLight.pixels -> show();
      delay(500);
      ringLight.pixels -> clear();
      ringLight.pixels -> show();
      delay(500);
      ringLight.setAsOneColor(0, 0, 255);
      ringLight.pixels -> show();
      delay(500);
      ringLight.pixels -> clear();
      ringLight.pixels -> show();
      delay(500);
    }
  }
  
  void doWinnerStuff(){
    uint8_t firstpos[2];
    uint8_t secondpos[2];
    uint8_t winner = manager -> checkWinner(firstpos, secondpos);
    if (winner == 1){
      danceTie();
    }
    else if (winner == 2){
      danceWin(firstpos[0], firstpos[1], secondpos[0], secondpos[1]);
    }
    if (winner != 0){
      manager -> reset();
      manager -> runUntilFinished();
      playing = false;
      headX = 0;
      headY = 0;
      delay(1000);
      manager -> reset();
      manager -> runUntilFinished(); // We can't rely on it to not change later, so we insure it.
    }
  }
};

struct TwoPlayerGame : public Game{
  FourJoystick *player1Joystick;
  PushButton *player1Button;
  FourJoystick *player2Joystick;
  PushButton *player2Button;
  
  TwoPlayerGame(Grid *management, FourJoystick *joy1, PushButton *but1, FourJoystick *joy2, PushButton *but2) : Game(management){    
    player1Joystick = joy1;
    player1Button = but1;
    
    player2Joystick = joy2;
    player2Button = but2;
  }
  
  void run(){
    Game::run(); // Need to call the original.
    player1Joystick -> poll();
    player2Joystick -> poll();
    player1Button -> poll();
    player2Button -> poll();
    if (turn){
      headX += player1Joystick -> getXChange();
      headY += player1Joystick -> getYChange();
    }
    else{
      headX += player2Joystick -> getXChange();
      headY += player2Joystick -> getYChange();
    }
    if (((turn && player1Button -> wasButtonReleased()) || (!turn && player2Button -> wasButtonReleased())) && !manager -> positionOccupied(headX, headY)){
      manager -> playPiece(turn, headX, headY);
      manager -> runUntilFinished(); // No interruptions here!
      turn = !turn;
    }
    manager -> moveToAPosition(headX, headY);
  }
};

struct DemonstrationGame : public Game{
  RecordedGame *recordedGames;
  uint8_t gamesNumber;
  bool playingRecordedGame = false;
  RecordedGame curGame;
  uint8_t curGameNumber;
  uint8_t curMove;
  DemonstrationGame(Grid *management, RecordedGame *games, uint8_t numberOfGames) : Game(management){
    recordedGames = games;
    gamesNumber = numberOfGames;
  }
  void doWinnerStuff(){
    Game::doWinnerStuff();
    playing = true; // NEVER exit the playing loop for this one.
  }
  void newGame(){
    curGameNumber = random(gamesNumber);
    curGame = recordedGames[curGameNumber];
    playingRecordedGame = true;
    curMove = 0;
    Game::newGame();
  }
  void run(){
    if (playingRecordedGame){
      if (manager -> isFinished()){
        manager -> playPiece(turn, curGame.moves[curMove].x, curGame.moves[curMove].y);
        turn = !turn;
        curMove ++;
        if (curMove > curGame.length - 1){
          playingRecordedGame = false;
        }
      }
    }
    turn = !turn; // v
    Game::run();
    turn = !turn; // ^ These cancel out
  }
};
