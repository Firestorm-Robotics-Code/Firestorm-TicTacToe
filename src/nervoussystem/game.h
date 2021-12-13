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
 
struct Game{
  Grid *manager;
  bool playing = false;

  NeoPixelController ringLight{12, 22};
  LightsController *lightGrid;

  bool turn = true;
  bool hasLights = false;
  uint8_t headX = 0;
  uint8_t headY = 0;

  bool oldTurn = true;

  Game(Grid *management){
    manager = management;
  }

  void assignLights(LightsController *lights){
    lightGrid = lights;
    hasLights = true;
  }

  virtual void tasks(){ // Leave it empty so we're just overriding it in the children. Virtual makes it overridable.
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
    if (turn != oldTurn){
      if (!turn){
        ringLight.swirly(255, 0, 0, 125);
      }
      else{
        ringLight.swirly(0, 0, 255, 125);
      }
      oldTurn = turn;
    }
    if (manager -> isFinished()){
      doWinnerStuff();
    }
    tasks();
    if (Serial.available()){
      String data = "";
      while (Serial.available()){
        data += Serial.readString(); // Read out everything.
      }
      if (data.substring(0, 5) == "place"){ // place 1 1 plays in the center. Allows me to do simulations without walking a lot.
        manager -> playPiece(turn, data.substring(6, 7).toInt(), data.substring(8, 9).toInt());
        manager -> runUntilFinished();
        turn = !turn;
      }
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
    lightGrid -> animate(A_CHANT_TIE);
  }
  
  void danceWin(int x1, int y1, int x2, int y2){
    if (!turn){
      lightGrid -> animate(A_CHANT_X);
    }
    else{
      lightGrid -> animate(A_CHANT_O);
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
      playing = false;
      headX = 0;
      headY = 0;
      manager -> reset();
      manager -> runUntilFinished();
      delay(1000);
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
  
  void tasks(){ // No longer need to call Game::run.
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
    if (hasLights){
      lightGrid -> setCursorPos(headX, headY);
      lightGrid -> drawCursor();
    }
    else{
      manager -> moveToAPosition(headX, headY);
    }
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
  }
  void newGame(){
    curGameNumber = random(0, gamesNumber);
    Serial.print("Random game number: ");
    Serial.println(curGameNumber);
    curGame = recordedGames[curGameNumber];
    playingRecordedGame = true;
    curMove = 0;
    Game::newGame();
  }
  void tasks(){
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
  }
};

struct OnePlayerGame : public Game{
  FourJoystick *player1Joystick;
  PushButton *player1Button;
  void (*autoFunction)(uint8_t[3][3], bool, uint8_t*);
  
  OnePlayerGame(Grid *management, FourJoystick *joy1, PushButton *but1, void (*function)(uint8_t[3][3], bool, uint8_t*)) : Game(management){    
    player1Joystick = joy1;
    player1Button = but1;
    autoFunction = function;
  }
  
  void tasks(){
    player1Joystick -> poll();
    player1Button -> poll();
    if (turn){
      headX += player1Joystick -> getXChange();
      headY += player1Joystick -> getYChange();
      if (player1Button -> wasButtonReleased() && !manager -> positionOccupied(headX, headY)){
        manager -> playPiece(turn, headX, headY);
        manager -> runUntilFinished(); // No interruptions here!
        turn = !turn;
      }
      manager -> moveToAPosition(headX, headY);
    }
    else{
      uint8_t marvin[2];
      autoFunction(manager -> grid, turn, marvin); // Yucky, but this can be smoothed out later.
      if (!manager -> positionOccupied(marvin[0], marvin[1])){
        manager -> playPiece(turn, marvin[0], marvin[1]);
        manager -> runUntilFinished();
        turn = !turn;
      }
      else{
        Serial.println("no.");
      }
    }
  }
};
