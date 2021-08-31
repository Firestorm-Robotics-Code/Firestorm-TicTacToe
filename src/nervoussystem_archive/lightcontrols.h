/* By Tyler Clarke, circa 2021 AD
 *  Controls lights in a properly configured P1AM, as well as NeoPixels wired straight to the Arduino
 */

#include <Adafruit_NeoPixel.h>

namespace lights{
  char data[8] = "\0\0\0\0\0\0\0\0";
  boll ready = false;
  boll helloSent = false;
  void _ROUTINE(int opcode, HardwareSerial coms){ // Opcodes: 1: hello, 2: blank, 3: chant
    if (!ready){
      if (!helloSent || opcode == 1){
        coms.write(1);
      }
    }
    else{
      switch (opcode){
        case 3:
          coms.write(2);
        break;
        case 4:
          coms.write(3);
          coms.write(data);
        break;
      }
      if (!opcode == 2){
        coms.write(data);
      }
    }
    if (coms.available()){
      char data = coms.read();
      if (data == 1){ // Hello acknowledged!
        ready = true;
      }
    }
  }
  void hello(HardwareSerial coms){
    _ROUTINE(1, coms);
  }
  void run(HardwareSerial coms){
    _ROUTINE(2, coms);
  }
  void wait_until_ready(HardwareSerial coms){
    while (!ready){
      _ROUTINE(2, coms);
    }
  }
  void chant(HardwareSerial coms, uint8_t chant){
    data[0] = chant;
    _ROUTINE(3, coms);
  }
  void movePiece(HardwareSerial coms, uint8_t x, uint8_t y, uint8_t x2, uint8_t y2){
    data[0] = x;
    data[1] = y;
    data[2] = x2;
    data[3] = y2;
    _ROUTINE(4, coms);
  }
}

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
