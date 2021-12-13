// There is a trick to making sure you don't forget to code stuff. It is a simple trick, too.
// If you want to do a boolean switch, and don't know what code you'll put in the true case but want a false case (else)
// You just leave the if empty. Unfortunately, that's easy to forget and cause you a headache.
// The solution? Put "#NOCOMPILE" in the body. It won't compile - because #NOCOMPILE is a fake directive.
// That's your lesson for today!

// Development status: near completion
/* Tasks left: (In semi-chronological order - follow the list as best as you can.)
 *   Finish control panel interface (do this in parts through-out the other development processes as needed)
 *   Build demonstration-mode
 *   Add at least 5 demo games
 *   Check up on Lawson's minimax
 *   Build one-player-mode
 */
// Joystick pins:
#define JOYSTICK_1_UP 32
#define JOYSTICK_1_DOWN 33
#define JOYSTICK_1_LEFT 34
#define JOYSTICK_1_RIGHT 31

#define JOYSTICK_2_UP 37
#define JOYSTICK_2_DOWN 38
#define JOYSTICK_2_LEFT 39
#define JOYSTICK_2_RIGHT 36

// Y motor one:
#define YMOTOR1_PUL 44
#define YMOTOR1_DIR 45
#define YMOTOR1_SWITCH 12

// Y motor two:
#define YMOTOR2_PUL 47
#define YMOTOR2_DIR 48
#define YMOTOR2_SWITCH 13

// X motor:
#define XMOTOR_PUL 50
#define XMOTOR_DIR 51
#define XMOTOR_SWITCH 11

// Grabber mechanism:
#define MAGNET 9
#define ACTUATOR 10

// Selector switch:
#define SELECTOR1 41
#define SELECTOR3 42

// Buttons:
#define PLAYBUTTON_1 35
#define PLAYBUTTON_2 40
#define STARTBUTTON 43


/* Further information:
 *  Cheat: Perform the Konami Code (minus the B-A part) in 5 seconds and one of the enemy pieces is removed. (NOT YET IMPLEMENTED).
 */

typedef bool boll; // This is a tribute to Lawson, pooooooooooooooooooooooooooooooooooop

#include "errors.h" // Must come first, the other guys use it.                     Will be OOPed.
#include "motor.h" // This contains class(es) to control motors.                   Fully OOPed.
#include "grid.h" // This contains class(es) to manage the grid.                   Fully OOPed.
#include "lightcontrols.h" // These manage lights, which are not yet implemented.  Will be OOPed.
#include "controlpanel.h" // A set of classes for joysticks and buttons.           Fully OOPed.
#include "game.h" // Classes for game management                                   Fully OOPed.
#include "auto.h" // Functions for AI player                                       FOP - needs to evolve to WbO.
#include "debug.h" // Debugging instructions;                                      Will be OOPed.
// TODO: Make all these codes a bit more object oriented.

Play basic_test[5] = { // An array of "play" objects, each of which is [type, x, y], for preset games.
  {1, 1}, // O at center
  {1, 0}, // X at one down from center
  {0, 1}, // O at one left from center
  {0, 0}, // X at bottom
  {2, 1} // O at one right from center, winning the game
};

Play brandonsGame[] = {
  {0, 2},
  {2, 2},
  {2, 0},
  {1, 1},
  {0, 0},
  {0, 1},
  {1, 0}
};

Play tie[] = {
  {1, 1},
  {2, 2},
  {1, 2},
  {1, 0},
  {2, 0},
  {0, 2},
  {0, 1},
  {2, 1},
  {0, 0}
};

RecordedGame allGames[] = {
  {basic_test, 5},
  {brandonsGame, 7},
  {tie, 9}
};


Motor xmotor(XMOTOR_PUL, XMOTOR_DIR, true, XMOTOR_SWITCH, false, 24 * 800); // X motor object.
Motor ymotor(YMOTOR1_PUL, YMOTOR1_DIR, true, YMOTOR1_SWITCH, false, 24 * 800); // First Y motor object.
Motor ymotorTwo(YMOTOR2_PUL, YMOTOR2_DIR, true, YMOTOR2_SWITCH, false, 24 * 800); // Second Y motor object.

// Lights
LightsController lights(&Serial1);

// Grid object
Grid manager(&xmotor, &ymotor, &ymotorTwo, 4094      , MAGNET    , ACTUATOR    , 12 * 800 + 912 - 2047, 12 * 800 + 125       , -4094, -4094             , -8460 + 100, -8189 , 8360 - 25, -8189 + 100);
//           X motor, y motor(s)         , tile width, magnet pin, actuator pin, x and y offset                              , tic-tac-toe grid x and y , O row x and y      , X row x and y
// These numbers are calculated based on the CAD model. If we run into issues, redo the measurements in inches and multiply by 800 for each.

FourJoystick joystick1(JOYSTICK_1_UP, JOYSTICK_1_DOWN, JOYSTICK_1_LEFT, JOYSTICK_1_RIGHT); // Player one joystick
PushButton endTurn1(PLAYBUTTON_1); // Player 1 button

FourJoystick joystick2(JOYSTICK_2_UP, JOYSTICK_2_DOWN, JOYSTICK_2_LEFT, JOYSTICK_2_RIGHT); // Player two joystick
PushButton endTurn2(PLAYBUTTON_2); // Player 2 button

PushButton start(STARTBUTTON); // Start button
ThreeSelectorSwitch gameMode(SELECTOR1, SELECTOR3); // Mode select. This one is interesting because the only digital pins are for mode 1 and mode 3 - you know its on mode 2 if neither trigger.

TwoPlayerGame twoPlayerMode(&manager, &joystick1, &endTurn1, &joystick2, &endTurn2);
DemonstrationGame demonstrationMode(&manager, allGames, 3);
OnePlayerGame onePlayerMode(&manager, &joystick1, &endTurn1, &AI_nope);

void setup(){ /* Setup code here. */
  Serial.begin(9600); // Start Serial.
  Serial1.begin(9600); // Connect to the light controller.
  manager.setSpeed(800 * 10); // One inch per second is 800, so all of the motors are set to 3x.
  xmotor.setSpeed(800 * 10); // Override the manager; change the X motor to 4x because it can go faster without breaky-breaky-ing.
  manager.zero();
  randomSeed(analogRead(A0));
  twoPlayerMode.assignLights(&lights);
}

void loop(){ /* This is the mainloop. */
  if (Serial.available()){
    Serial.println("You'd best be careful with serial connections; I am very sarcastic.");
    if (Serial.readString().substring(0,5) == "debug"){
      Serial.println("Entering debug mode. You can type 'help' all you want, but you won't get anywhere.");
      while (debugMode(lights));
      Serial.println("Exited debug mode.");
    }
  }
  manager.run();
  gameMode.poll();
  start.poll();
  if (start.wasButtonReleased() && !twoPlayerMode.playing && !onePlayerMode.playing){ // When 1-player-mode is in it should be added in the same way the two Player Mode was added.
    manager.zero();
    if (demonstrationMode.playing){
      demonstrationMode.playing = false;
      manager.cancel();
    }
    if (gameMode.position == 0){
      demonstrationMode.newGame();
    }
    if (gameMode.position == 1){
      onePlayerMode.newGame();
    }
    if (gameMode.position == 2){
      twoPlayerMode.newGame();
    }
  }
  if (twoPlayerMode.playing){
    twoPlayerMode.run();
  }
  else if (onePlayerMode.playing){
    onePlayerMode.run();
  }
  else if (demonstrationMode.playing){
    demonstrationMode.run();
  }
}
/* Sample gameplay:
 *  First, set selector to 1v1 and press game start. It will reset the board if necessary and will zero.
 */
