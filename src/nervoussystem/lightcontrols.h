/* By Tyler Clarke, circa 2021 AD
 *  Controls lights in a properly configured P1AM, as well as NeoPixels wired straight to the Arduino
 */

#include <Adafruit_NeoPixel.h>

#define ASK 1
#define ASK_IS_FINISHED 1

#define ANIMATE 1
#define A_CHANT_X 1
#define A_CHANT_O 2
#define A_CHANT_TIE 3

#define INSTANT 2
#define I_CURSOR_DRAW 1
#define I_CURSOR_SET_POS 2
#define I_CURSOR_SET_COLOR 3
#define I_CURSOR_ERASE 4

struct LightsController{
  HardwareSerial *coms;
  bool blocking;
  
  LightsController(HardwareSerial *serial){
    coms = serial;
  }
  
  void setBlocking(bool block){
    blocking = block;
  }

  void waitUntilFinished(){
    while (coms -> available() == 0);
    int garbage = coms -> read(); // NEEDSFIX: Need to fix the type, eventually
    // I'm very eww: I constantly mix up "Serial" and "coms". Gotta get over my weird insanity.
    if (!(garbage == 1)){
      unknownfault("The light controller is not responding correctly. Give the connection a cursory examination; if it does not give results, do NOT mess with it further.", "lightcontrols.h::LightsController::waitUntilFinished::if.1");
      Serial.print("Light controller responded: ");
      Serial.println(garbage);
    }
  }

  void animate(uint8_t opcode){
    coms -> write(ANIMATE);
    coms -> write(opcode);
  }

  void setCursorPos(uint8_t x, uint8_t y){
    coms -> write(INSTANT);
    coms -> write(I_CURSOR_SET_POS);
    coms -> write(x);
    coms -> write(y);
    drawCursor();
  }

  void setCursorColor(bool color){
    coms -> write(INSTANT);
    coms -> write(I_CURSOR_SET_COLOR);
    coms -> write(color);
    drawCursor();
  }

  void drawCursor(){
    coms -> write(INSTANT);
    coms -> write(I_CURSOR_ERASE);
    waitUntilFinished(); // So we don't have buffer overflow
    coms -> write(INSTANT);
    coms -> write(I_CURSOR_DRAW);
  }
};

struct NeoPixelController{
  uint8_t numLights;
  Adafruit_NeoPixel *pixels;
  NeoPixelController(uint8_t numberOfLights, int pin){
    pixels = new Adafruit_NeoPixel(numberOfLights, pin, NEO_GRB + NEO_KHZ800);
    numLights = numberOfLights;
    pixels -> begin();
  }
  void swirly(uint8_t r, uint8_t g, uint8_t b, unsigned int delval){
    for (uint8_t i = 0; i < numLights; i ++){
      pixels -> setPixelColor(i, pixels -> Color(r, g, b));
      pixels -> show();
      delay(delval);
    }
  }
  void setAsOneColor(uint8_t r, uint8_t g, uint8_t b){
    for (uint8_t i = 0; i < numLights; i ++){
      pixels -> setPixelColor(i, pixels -> Color(r, g, b));
    }
    pixels -> show();
  }
};
