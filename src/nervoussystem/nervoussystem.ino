#include <SoftwareSerial.h>
#define RX 2
#define TX 3

struct theFunnyStructMan{
  int longHill;
}

SoftwareSerial serial{RX, TX};
theFunnyStructMan *foobo;
char* thePointer;

void sendAllTheThings(){
  thePointer = foobo;
  for (int i = 0; i < sizeof(foobo); i++){
    serial.write(thePointer[i]);
  }
}

void setup(){ /* Setup code here. */
  
}

void loop(){ /* This is the mainloop. */
  foobo -> longHill++;
  sendAllTheThings();
}
