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
 *  Enter debugging mode: Go to demonstration mode and press the start button three times in quick succession (<3 seconds).
 *  Cheat: Perform the Konami Code (minus the B-A part) in 5 seconds and win instantaneously.
 */

/* Hardware fault logging paradigm:
 *  Every log message MUST begin with "<type> FAULT DETECTED - ".
 *  Types may be SOFTWARE or HARDWARE.
 *  Every log message must then provide a brief summary of the problem, e.g. "The selector switch is broken"
 *  Every log message must then provide the logic location of the fault report, in the format file::class::function::logic-level-1::logic-level-2...::logic-level-n.
 *  Every log message may finally include instructions to solve the issue, but only if the issue is easily solved.
 */

typedef bool boll; // This is a tribute to Lawson

#include "motor.h" // This contains class(es) to control motors.
#include "grid.h" // This contains class(es) to manage the grid.
#include "lightcontrols.h" // These manage lights, which are not yet implemented.
#include "controlpanel.h" // A set of classes for joysticks and buttons.
#include "game.h" // Classes for game management
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

// WE SERIOUSLY NEED A BLEED RESISTOR TO PULL THE RELAY DOWN, OR THE BEPRO PEOPLE ARE IN FOR A **NASTY** SURPRISE!!!!!

Motor xmotor(XMOTOR_PUL, XMOTOR_DIR, true, XMOTOR_SWITCH, false, 24 * 800); // X motor object.
Motor ymotor(YMOTOR1_PUL, YMOTOR1_DIR, true, YMOTOR1_SWITCH, false, 24 * 800); // First Y motor object.
Motor ymotorTwo(YMOTOR2_PUL, YMOTOR2_DIR, true, YMOTOR2_SWITCH, false, 24 * 800); // Second Y motor object.

// Grid object:
Grid manager(&xmotor, &ymotor, &ymotorTwo, 4094      , MAGNET    , ACTUATOR    , 12 * 800 + 912 - 2047, 12 * 800 + 125        , -4094, -4094             , -8460 + 100, -8189 , 8360 - 25, -8189 + 100);
//           X motor, y motor(s)         , tile width, magnet pin, actuator pin, x and y offset                              , tic-tac-toe grid x and y , O row x and y      , X row x and y
// These numbers are calculated based on the CAD model. If we run into issues, redo the measurements in inches and multiply by 800 for each.

FourJoystick joystick1(JOYSTICK_1_UP, JOYSTICK_1_DOWN, JOYSTICK_1_LEFT, JOYSTICK_1_RIGHT); // Player one joystick
PushButton endTurn1(PLAYBUTTON_1); // Player 1 button

FourJoystick joystick2(JOYSTICK_2_UP, JOYSTICK_2_DOWN, JOYSTICK_2_LEFT, JOYSTICK_2_RIGHT); // Player two joystick
PushButton endTurn2(PLAYBUTTON_2); // Player 2 button

PushButton start(STARTBUTTON); // Start button
ThreeSelectorSwitch gameMode(SELECTOR1, SELECTOR3); // Mode select. This one is interesting because the only digital pins are for mode 1 and mode 3 - you know its on mode 2 if neither trigger.

TwoPlayerGame twoPlayerMode(&manager, &joystick1, &endTurn1, &joystick2, &endTurn2);
DemonstrationGame demonstrationMode(&manager, allGames, 1);

void setup(){ /* Setup code here. */
  Serial.begin(9600); // Start Serial.
  manager.setSpeed(800 * 3); // One inch per second is 800, so all of the motors are set to 3x.
  xmotor.setSpeed(800 * 4); // Change the X motor to 4x.
  manager.zero();
}

bool debugMode(){ // Debugging mode. Activates if the command "debug" is sent from a computer.
  if (Serial.available()){
    String data = Serial.readString();
    Serial.println(data);
    if (data.substring(0,5) == "xmove"){
      xmotor.move(data.substring(6).toInt());
    }
    else if (data.substring(0, 5) == "ymove"){
      ymotor.move(data.substring(6).toInt());
      Serial.println("Request acknowledged.");
    }
    else if (data.substring(0, 6) == "xspeed"){
      xmotor.setSpeed(data.substring(7).toInt());
    }
    else if (data.substring(0, 6) == "yspeed"){
      ymotor.setSpeed(data.substring(7).toInt());
    }
    else if (data.substring(0, 5) == "yzero"){
      ymotor.zeroTwo(400, &ymotorTwo);
    }
    else if (data.substring(0, 4) == "exit"){
      return false;
    }
  }
  xmotor.run();
  ymotor.run();
  return true;
}

void loop(){ /* This is the mainloop. */
  if (Serial.available()){
    if (Serial.readString() == "debug"){
      while (debugMode());
    }
  }
  manager.run();
  gameMode.poll();
  start.poll();
  if (start.wasButtonReleased() && !twoPlayerMode.playing){ // When 1-player-mode is in it should be added in the same way the two Player Mode was added.
    if (demonstrationMode.playing){
      demonstrationMode.playing = false;
      manager.cancel();
    }
    if (gameMode.position == 0){
      demonstrationMode.newGame();
    }
    if (gameMode.position == 2){
      twoPlayerMode.newGame();
    }
  }
  if (twoPlayerMode.playing){
    twoPlayerMode.run();
  }
  else if (demonstrationMode.playing){
    demonstrationMode.run();
  }
}
/* Sample gameplay:
 *  First, set selector to 1v1 and press game start. It will reset the board if necessary and will zero.
 */
