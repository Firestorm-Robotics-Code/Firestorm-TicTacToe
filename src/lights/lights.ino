/* To make life easy, I will include a wiring map. Change as needed.
 *  Note that each ring is 24 pixels, and is labeled with the first-position to access it. The next one is obviously going to be the final point.
 ____     ____     ____  
/48  \___/72  \   /192 \
\____/   \____/   \____/  
 |___     |___     |___  
/24  \   /96  \   /168 \  
\____/   \____/   \____/  
 |___     |___     |___  
/0   \   /120 \___/144 \_____[END]  
\____/   \____/   \____/  
 |
 |
[CONTROLLER]

*/


#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN       11
#define NUMPIXELS 216
#define DELAYVAL  500

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial coms(13, 12);
uint32_t white = pixels.Color(255, 255, 255);
uint32_t red = pixels.Color(255, 0, 0);
uint32_t green = pixels.Color(0, 255, 0);
uint32_t blue = pixels.Color(0, 0, 255);
uint32_t black = pixels.Color(0, 0, 0);

bool player_is_red = false;

int getPixel(uint8_t x, uint8_t y, uint8_t num){
  if (x == 0){
    return 48 - (y * 24) + num;
  }
  else if (x == 1){
    return 72 + (y * 24) + num;
  }
  else if (x == 2){
    return 192 - (y * 24) + num;
  }
}

void setRing(uint8_t x, uint8_t y, uint32_t color){
  for (int i = 0; i < 24; i ++){
    pixels.setPixelColor(getPixel(x, y, i), color);
  }
}

void setup(){
  pinMode(8, INPUT);
  pinMode(9, OUTPUT);
  coms.begin(9600);
  Serial.begin(9600);
  pixels.begin();
  pixels.setBrightness(205); // 0.8 * 256 = 204.8; thus this is 80% power. Only 6 can be lit up before you have issues.
  setRing(0, 0, blue);
  setRing(0, 1, blue);
  setRing(0, 2, blue);
  setRing(2, 0, red);
  setRing(2, 1, red);
  setRing(2, 2, red);
  pixels.show();
  delay(5000);
  pixels.clear();
  pixels.show();
}
    
uint8_t x1; // Multi-purpose x-y pairings. Local variables inside case statements break.
uint8_t y1;
uint8_t x2;
uint8_t y2;
uint8_t x3;
uint8_t y3;

uint8_t cX = 0; // X position of the cursor
uint8_t cY = 0; // Y position of the cursor
bool    cC = true; // Color of the cursor; red or blue

void loop(){
  if (coms.available() > 1){
    uint8_t d = coms.read(); // Will improve this
    
    if (d == 1){ // Animations
      d = coms.read();
      switch (d){
        case 1:
          Serial.println("Chanting X");
          for (uint8_t x = 0; x < 4; x ++){
            setRing(0, 0, white);
            setRing(2, 2, white);
            setRing(2, 0, white);
            setRing(0, 2, white);
            setRing(1, 1, white);
            pixels.show();
            delay(1000);
            pixels.clear();
            pixels.show();
            delay(1000);
          }
          break;
        case 2:
          Serial.println("Chanting O");
          for (uint8_t x = 0; x < 4; x ++){
            setRing(1, 0, white);
            setRing(2, 1, white);
            setRing(1, 2, white);
            setRing(0, 1, white);
            pixels.show();
            delay(1000);
            pixels.clear();
            pixels.show();
            delay(1000);
          }
          break;
        case 3:
          // L
          pixels.clear();
          setRing(2, 0, blue);
          setRing(1, 0, blue);
          setRing(0, 0, blue);
          setRing(0, 1, blue);
          setRing(0, 2, blue);
          pixels.show();
          delay(2000);
          // O
          pixels.clear();
          setRing(1, 0, green);
          setRing(0, 1, green);
          setRing(2, 1, green);
          setRing(1, 2, green);
          pixels.show();
          delay(2000);
          // L
          pixels.clear();
          setRing(2, 0, blue);
          setRing(1, 0, blue);
          setRing(0, 0, blue);
          setRing(0, 1, blue);
          setRing(0, 2, blue);
          pixels.show();
          delay(2000);
          pixels.clear();
          pixels.show();
        }
      }
      else if (d == 2){ // Cursor and in-game effects
        Serial.println("Dat boy cursor");
        while (coms.available() == 0); // Got some crap data because the arduino was working faster than the serial connection. This fixes it (supposedly).
        d = coms.read();
        Serial.println(d);
        switch(d){
          case 1: // Draw cursor
            Serial.println("Draw!");
            setRing(cX, cY, cC ? red : blue);
            pixels.show();
            break;
          case 2: // Set cursor pos
            while (coms.available() == 0);
            cX = coms.read();
            while (coms.available() == 0);
            cY = coms.read();
            break;
          case 3: // Set cursor color
            while (coms.available() == 0);
            cC = coms.read();
            break;
          case 4: // Delete cursor
            setRing(cX, cY, black);
            pixels.show();
            break;
        }
      }
    coms.write(1);
  }
}
