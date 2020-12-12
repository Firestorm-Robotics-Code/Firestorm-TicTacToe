#define X_PUL 12 // It turns out I was wrong: it doesn't have to be a real PWM pin. Software PWM is a thing and works.
#define X_DIR 11 // Or maybe 12 is a PWM as well - It shouldn't matter
// Two motors are on X, so only four pins

#define Y_PUL 7
#define Y_DIR 6

#define SQUARESIZE 5 // Just a guesstimation. Will change this to something real later - when someone on Engineering shows up.

#define GRIDSIZE 3 // Three squares on every side - not a necessary definition but still

#define GRIDSTART_X SQUARESIZE // First x position of the grid - probably one square from zero which is my estimation

#define GRIDSTART_Y SQUARESIZE // See above

#define ONE_INCH_ROTATIONS 8000

#define X_PIN A5

#define Y_PIN A6

#define RIGHT 45333.333

#define LEFT -45333.333

#define UP 45333.333

#define DOWN -45333.333
