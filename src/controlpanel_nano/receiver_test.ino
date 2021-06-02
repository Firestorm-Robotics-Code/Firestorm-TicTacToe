#include <SoftwareSerial.h>
#define RX 2
#define TX 3
char* theBooped;
void setup {
}
void loop {
  
}
void poopyhead (){
  SoftwareSerial serial{RX, TX};
  int i = 0; 
  while(Serial.available){
    i++
      theBooped[i] = Serial.read();
    } 
 }
