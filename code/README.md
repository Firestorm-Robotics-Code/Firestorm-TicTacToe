# This is the directory for actual code on the TicTacToe.

Add more files as it becomes necessary - Every file should do one thing only.

`code.ino` is a pulling-it-all-together file. Its also what you open in Arduino IDE, and should not contain any logic or anything but calls to the other files.

`logic.ino` should contain the Tic Tac Toe logic.

`Motor.ino` should contain code for controlling the motors

`constants.h` should contain only preprocessor commands (#define and other hashtag things).  
The preprocessor command for including a file is #include "filename_here". For including libraries, its the same thing but with lessthan/greaterthan symbols.

You can open this directory like any other arduino project - just navigate to the project and open up logic.ino.

## Operating system concerns:
* Windows users - Windows is, undeniably (you could also deny it, if you want to) the 2nd worst operating system for coding. Arduino will be doable on a Windows, but if you can use Linux or Mac, do.
* ChromeOS users - ChromeOS is the worst operating system for coders because it doesn't have arduino.
* Mac users - Mac gives a half-best-of-both-worlds experience - Its a mainstream OS but you still have a bit of coding ability with it. Not terrible, but not open source either.
* Linux users - Using linux makes you one step short of a god. Keep up the good work.
