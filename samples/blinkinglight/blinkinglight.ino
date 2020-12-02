// A simple blinking light scetch, with the purpose of showing basic Arduino syntax.
// First we have the definitions. These are all in the syntax #define NAME VALUE.

#define LEDPIN 11 // The LED should be wired to pin 11, with a resistor of some sort.

// Definitions are used by the preprocessor only. The preprocessor scans the file and, if it encounters a definition, replaces every occurence of NAME with VALUE, before it actually compiles.
// This is supposedly cleaner than using an int, and it probably is. 16 bit memory addresses means it would take up 32 bits (real number, memory address) as opposed to 16 bits (real number only).
// I don't know the limits, only that it gets exceedingly weird as you use numbers besides ints.

void setup(){// This runs on startup of the program, like int main in computer c++.
  pinMode(LEDPIN, OUTPUT); // Tells the Arduino processor to use the digital pin 8 for outputting voltage - probably 3.3 volts. OUTPUT is likely another definition. Maybe test what its value is, using Serial?
}

void loop(){// Runs for a theoretically infinite amount of time
  digitalWrite(LEDPIN, HIGH); // HIGH is probably another definition (also sometimes known as a macro).
  delay(1000); // Delay for a time in milliseconds. There's another one called delayMicroseconds which takes a value in millionths of a second, as opposed to thousandths.
  digitalWrite(LEDPIN, LOW); // LOW is another definition so far as I know
  delay(1000);
  for (int i = 10; i > 0; i-=1){ // Try to guess what this does... "C++ for loop" is the google for this one
    digitalWrite(LEDPIN, HIGH);
    delay(i * 100);
    digitalWrite(LEDPIN, LOW);
    delay(i * 100);
  }
}
