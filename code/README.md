# This is the directory for actual code on the TicTacToe.

Add more files as it becomes necessary - Every file should do one thing only.

`code.ino` is a pulling-it-all-together file. Its also what you open in Arduino IDE, and should not contain any logic or anything but calls to the other files.

`grid.ino` should depend on `motor.ino`, and give an api for moving the screws to any point on the tic tac toe board. `constants.h` should contain rotations-per-centimeter and other such information.

`logic.ino` should contain the Tic Tac Toe logic. Should depend on `grid.ino` for moving things.

`motor.ino` should contain code for controlling a two-wire motor. This will be used in preference to AccelStepper.

`constants.h` should contain only preprocessor commands (#define and other hashtag things).

You can open this directory like any other arduino project - just navigate to the project and open up code.ino.

## Operating system concerns:
* Windows users - Windows is, undeniably (you could also deny it, if you want to) the 2nd worst operating system for coding. Arduino will be doable on a Windows, but if you can use Linux or Mac, do.
* ChromeOS users - ChromeOS is the worst operating system for coders because it doesn't have arduino.
* Mac users - Mac gives a half-best-of-both-worlds experience - Its a mainstream OS but you still have a bit of coding ability with it. Not terrible, but not open source either.
* Linux users - Using linux makes you one step short of a god. Keep up the good work.

## Other concerns:
* Arduino will auto-concatenate all files in this project, so no #includes. Make sure not to leave any functions 'dangling' - use a class, or a namespace if you absolutely have to.
