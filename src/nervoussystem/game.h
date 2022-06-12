/* By Tyler Clarke
 *  
 *  Classes for game management. Makes it more organized.
 *  
 *  Simple game workflow:
 *  Create object "game" of the Game class
 *  In void loop, do:
if (game.playing){
  game.run();
}
 */

struct Game; // Predefinition.


struct Controller {
  virtual void run(Game* game){} // Override this.
  virtual void newGame(){} // Override this too.
};


struct Game{
  Grid *manager;
  Controller *player1;
  Controller *player2;
  bool playing = false;

  NeoPixelController ringLight{12, 22};
  LightsController *lightGrid;

  bool turn = true;
  bool hasLights = false;
  uint8_t headX = 0;
  uint8_t headY = 0;

  bool oldTurn = true;

  Game(Grid *management, Controller* p1, Controller* p2){
    manager = management;
    player1 = p1;
    player2 = p2;
  }

  void assignLights(LightsController *lights){
    lightGrid = lights;
    hasLights = true;
  }
  
  bool run(){
    if (turn){
      player1 -> run(this);
    }
    else{
      player2 -> run(this);
    }
    
    if (turn != oldTurn){
      if (turn){
        ringLight.swirly(255, 0, 0, 125);
      }
      else{
        ringLight.swirly(0, 0, 255, 125);
      }
      oldTurn = turn;
    }
    
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
      if (doWinnerStuff()){
        Serial.println("It's working");
        return true;
      }
      // We don't want to exit the function if it returns false.
    }

    if (hasLights){
      lightGrid -> setCursorPos(headX, headY);
    }
    manager -> moveToAPosition(headX, headY);
    // Dev stuff
    if (Serial.available()){
      String data = "";
      while (Serial.available()){
        data += Serial.readString(); // Read out everything.
      }
      if (data.substring(0, 5) == "place"){ // place 1 1 plays in the center. Allows me to do simulations without walking a lot.
        uint8_t x = data.substring(6, 7).toInt();
        uint8_t y = data.substring(8, 9).toInt();
        manager -> playPiece(turn, x, y);
        manager -> runUntilFinished();
        turn = !turn;
      }
    }
    return false;
  }

  void place(){
    if (!manager -> positionOccupied(headX,headY)){
      if (hasLights){
        lightGrid -> setPiece(turn, headX, headY);
      }
      manager -> playPiece(turn, headX, headY);
      manager -> runUntilFinished();
      turn = !turn;
    }
  }
  
  void newGame(){
    player1 -> newGame();
    player2 -> newGame();
    turn = true;
    playing = true;
    if (turn){
      ringLight.swirly(255, 0, 0, 125);
    }
    else{
      ringLight.swirly(0, 0, 255, 125);
    }
  }

  void danceTie(){
    lightGrid -> animate(A_CHANT_TIE);
  }
  
  void danceWin(int x1, int y1, int x2, int y2){
    if (turn){
      lightGrid -> animate(A_CHANT_X);
    }
    else{
      lightGrid -> animate(A_CHANT_O);
    }
  }
  
  bool doWinnerStuff(){
    uint8_t firstpos[2];
    uint8_t secondpos[2];
    uint8_t winner = manager -> checkWinner(firstpos, secondpos);
    if (winner == 1){
      danceTie();
    }
    else if (winner == 2){
      danceWin(firstpos[0], firstpos[1], secondpos[0], secondpos[1]);
    }
    if (winner != 0){ // Either case
      playing = false;
      headX = 0;
      headY = 0;
      manager -> reset();
      manager -> runUntilFinished();
      newGame(); // Defaultify settings for a game.
      delay(1000);
      return true;
    }
    return false;
  }

  void cheat(){
    manager -> runUntilFinished();
    manager -> cheat(turn);
  }
};


struct JoystickController : Controller {
  FourJoystick* mjoy;
  PushButton* mbut;
  uint8_t konami = 0;
  void assign(FourJoystick* joy, PushButton* but){
    mjoy = joy;
    mbut = but;
  }
  
  void run(Game* game){
    mjoy -> poll();
    if (mjoy -> rightReleased()){
      game -> headX ++;
      if (konami == 0 || konami == 2){
        konami ++;
        Serial.println("Hur hur 1");
      }
      else{
        konami = 0;
      }
    }
    if (mjoy -> leftReleased()){
      game -> headX --;
      if (konami == 1 || konami == 3){
        konami ++;
        Serial.println("Hur hur 2");
      }
      else{
        konami = 0;
      }
    }
    if (mjoy -> downReleased()){
      game -> headY --;
      if (konami == 6){
        konami ++;
        Serial.println("Hur hur 3");
      }
      else if (konami == 7){
        Serial.println("Hur hur");
        game -> cheat();
      }
      else{
        konami = 0;
      }
    }
    if (mjoy -> upReleased()){
      game -> headY ++;
      if (konami == 4 || konami == 5){
        konami ++;
      }
      else{
        konami = 0;
      }
    }
    mbut -> poll();
    if (mbut -> wasButtonReleased()){
      game -> place();
    }
  }
};

struct ComputerController : Controller{
  void run(Game* game){
    game -> headX = random(0, 3);
    game -> headY = random(0, 3);
    game -> place();
  }
};

struct Play{
  int x;
  int y;
};

struct RecordedGame{
  Play* moves;
  uint8_t length;
};

struct DemonstrationController : Controller{
  RecordedGame *recordedGames;
  int gameNum;
  int moveNum = 0;
  unsigned int numGames;
  bool postThisTime = false;
  void run(Game* game){
    if (postThisTime){
      delay(500);
      game -> place();
      postThisTime = false;
    }
    else{
      game -> headX = recordedGames[gameNum].moves[moveNum].x;
      game -> headY = recordedGames[gameNum].moves[moveNum].y;
      moveNum ++;
      postThisTime = true;
    }
  }

  void assign(RecordedGame *regame, unsigned int len){
    recordedGames = regame;
    numGames = len;
    Serial.print("New game len: ");
    Serial.println(len);
    Serial.println(numGames);
  }

  void newGame(){
    Serial.println("I don't suck");
    gameNum = random(0, numGames);
    Serial.println(numGames);
    Serial.println(gameNum);
    moveNum = 0;
  }
};
