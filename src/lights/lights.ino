/* To make life easy, I will include a wiring map. Change as needed.
 *  Note that each ring is 24 pixels, and is labeled with the first-position to access it. The next one is obviously going to be the final point.
 ____     ____     ____  
/48  \_  /72  \_  /190 \
\____/ | \____/ | \____/  
 |___  |  |___  |  |___  
/24  \ | /96  \ | /166 \  
\____/ | \____/ | \____/  
 |___  |  |___  |  |___  
/0   \ |_/118 \ |_/142 \_____[END]  
\____/   \____/   \____/  
 |
 |
[CONTROLLER]

*/


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN       UNKNOWN_WONTCOMPILE
#define NUMPIXELS 214

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

Serial coms(13, 14);

void setup(){
  pixels.begin();
}

int getRingPos(x, y){
  return (x * 3) + y;
}

void loop(){
  pixels.clear();
  char data = coms.read();
  if (data == 1){
    coms.write(1);
  }
  else if (data == 2){
    char chant = coms.read();
    if (chant == 0){ // O - A white flashing O
      int one = getRingPos(0, 1);
      int two = getRingPos(1, 0);
      int three = getRingPos(2, 1);
      int four = getRingPos(1, 2);
      for (int x = 0; x < 5; x ++){
        for (int z = 0; z < 24; z ++){
          pixels.setPixelColor(z + one, pixels.Color(255, 255, 255));
          pixels.setPixelColor(z + two, pixels.Color(255, 255, 255));
          pixels.setPixelColor(z + three, pixels.Color(255, 255, 255));
          pixels.setPixelColor(z + four, pixels.Color(255, 255, 255));
        }
        delay(500);
        pixels.clear();
        delay(500);
      }
    }
    else if (chant == 1){ // X - A white flashing x
      int one = getRingPos(0, 0);
      int two = getRingPos(1, 1);
      int three = getRingPos(2, 0);
      int four = getRingPos(2, 2);
      int five = getRingPos(0, 2);
      for (int x = 0; x < 5; x ++){
        for (int z = 0; z < 24; z ++){
          pixels.setPixelColor(z + one, pixels.Color(255, 255, 255));
          pixels.setPixelColor(z + two, pixels.Color(255, 255, 255));
          pixels.setPixelColor(z + three, pixels.Color(255, 255, 255));
          pixels.setPixelColor(z + four, pixels.Color(255, 255, 255));
          pixels.setPixelColor(z + five, pixels.Color(255, 255, 255));
        }
        delay(500);
        pixels.clear();
        delay(500);
      }
    }
    else if (chant == 2){ // Starting chant - RGBBRGGBR layout, all ticking down (turning off along the circle incrementally)
      
    }
    else if (chant == 3){ // Error - All red and flashing
      
    }
    else if (chant == 4){ // Debug mode - All blue and flashing
      
    }
  }
  else if (data == 3){
    uint8_t x = coms.read();
    uint8_t y = coms.read();
    uint8_t x2 = coms.read();
    uint8_t y2 = coms.read();
  }
}
