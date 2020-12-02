// A scetch to play Happy Birthday on a Piezo buzzer - "piezoelectricity" (abstract) or "piezo buzzer" is the google for this one
// Check blinkinglight first

#define PIEZOPIN 9 // Check the Uno (these are all for uno). Digital 9 should have a tilde in front of the label - that means PWM or Pulse Width Modulation. Either of those is a good google.

// If 9 is a proper PWM pin, wire the red wire of a piezo buzzer (if they're uncoloured, it doesn't matter which wire) to the piezo pin and the black to a ground (again, doesn't really matter). 
// If not, change the definition to a PWM pin and proceed as normal. Here we see the beauty of preprocessor definitions.

void setup(){
  pinMode(PIEZOPIN, OUTPUT); // See blinkinglight
}

void playSound(int frequency, int duration, int pause){ // A function made by me, which plays a frequency in herts for an amount of time (in milliseconds) then waits for an amount of time (in milliseconds).
  tone(PIEZOPIN, frequency); // Plays a tone in hertz on the specified pin. This is handled by the internal Arduino timer, so we don't have to mess with it. It uses PWM, which you should definitely google.
  delay(duration/5); // Divided by five because I didn't want to divide all the numbers by five. Don't do this in any other program.
  noTone(PIEZOPIN); // Stops playing the tone on a pin.
  delay(pause/5); // Same as above.
}

void loop() {
  playSound(264, 250, 500); // Plays happy birthday, tones and delays extracted via a Python script from https://gist.github.com/krin-san/ef6b8b1e501ad4a82902.
  playSound(264, 250, 250); // As the Sirius Cybernetics Complaints Division says, Share and Enjoy!
  playSound(297, 1000, 250);
  playSound(264, 1000, 250);
  playSound(352, 1000, 250);
  playSound(330, 2000, 500);
  playSound(264, 250, 500);
  playSound(264, 250, 250);
  playSound(297, 1000, 250);
  playSound(264, 1000, 250);
  playSound(396, 1000, 250);
  playSound(352, 2000, 500);
  playSound(264, 250, 500);
  playSound(264, 250, 250);
  playSound(264, 1000, 250);
  playSound(440, 1000, 250);
  playSound(352, 500, 250);
  playSound(352, 250, 250);
  playSound(330, 1000, 250);
  playSound(297, 2000, 500);
  playSound(466, 250, 500);
  playSound(466, 250, 250);
  playSound(440, 1000, 250);
  playSound(352, 1000, 250);
  playSound(396, 1000, 250);
  playSound(352, 2000, 250);
}
