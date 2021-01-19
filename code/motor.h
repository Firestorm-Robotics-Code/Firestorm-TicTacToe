#include <Arduino.h>

// This is an alternative to AccelStepper, which will be specifically tailored to our needs. We will use this instead as it is less than 100 lines and very effecient - It worked on the first try (after I corrected a few type errors and included arduino.h)

// Need to verify that this code works

class Motor{ // Reserve the class name Motor. Redefinition will wonk.
  public:
    long pos = 0; // Long allows for very large position values, with a signed 32 bits. If it seems small, consider how long you could live on 2 billion dollars. (hint: you could spend 1000 dollars a day for around five thousand five hundred years - from the biblical start of the universe to Shakespearean times. You could buy Moses a yacht to make his journey across the ocean easier, and then get front row seats to Hamlet. 
    
    long goal = 0; // Same
    
    bool curdir = false; // Bool is the most effecient type because it theoretically only uses 1 bit. I'm not sure how this plays out as far as memory is concerned, but it at least uses less space than the barbarous 16-bit integer.

    int dirpin; 
    
    int pulpin;
    
    int stage=0;
    
    unsigned long speed = 1000; // Speed is in steps per second.
    
    unsigned long lastMicrosPul=0; // Last microseconds value for the pulse. Unsigned long is the return type of the micros function.
    
    unsigned long lastMicrosDir=0; // Last microseconds value for the direction
    
    Motor(int pul, int dir){
      dirpin=dir;
      pulpin=pul;
      pinMode(pul,OUTPUT); // At least PUL must be a PWM pin, as it has to pulse on and off rapidly.
      pinMode(dir,OUTPUT); // No timer controls on direction, which could eventually be a problem as 
    }
    
    long getDistance(){ // Return the distance to the goal
      return goal - pos;
    }
    
    void setSpeed(unsigned long newspeed){
      speed=newspeed;
    }
    
    void setGoal(long newgoal){
      goal = newgoal;
    }
    
    void move(int distance){
      goal += distance;
    }
    
    void run(){ // 20 microsecond pulse
      if (getDistance() < 0 && curdir == true){ // Boolean curdir value True = forwards, False = backwards.
        curdir = false; // Flip it back, to the right value.
        digitalWrite(dirpin, LOW); // This may be backwards - To any other coders who catch this: if this is actually reversed, just flip the "LOW" to "HIGH". This should reverse the direction that it considers "backwards".
      }
      
      if (getDistance() > 0 && curdir == false){ // These are flipped deliberately. The idea of these if conditions is to catch any situation in which they are wrong.
        curdir = true;
        digitalWrite(dirpin, HIGH); // If the other one was backwards, make this one LOW, to reverse the direction.
      }
      // The above if conditions may cause a problem with the direction flipping too soon before the pulse. This could result in the motors driving one step too far - if this becomes an issue, we may have to add a pause of five microseconds after this. For more information: https://cdn.automationdirect.com/static/manuals/leadshinestepper/dm322e.pdf. You can also find that link in the githubs README.md. I used page 13 mostly.

      if (stage == 0 && pos != goal){
        digitalWrite(pulpin, HIGH);
        lastMicrosPul = micros(); // Get the number of microseconds since start of the Arduino. Because MKRZero (the board we're emulating) has a 48 MHZ processor, this should return an absolute value.
        stage = 1;
      }

      if (stage == 1 && (micros() - lastMicrosPul) > 8){ // Minimum pulse width of 7.5 μs (microseconds). Half a microsecond is about 1/1500000th of the time it takes to load the google search results about the microsecond symbol, so I decided to just round up to 8 microseconds.
        digitalWrite(pulpin, LOW);
        lastMicrosPul = micros(); // Update the value, so we can keep the pulse "low" until another pulse is needed.
        stage = 2;
      }

      if (stage == 2 && (micros() - lastMicrosPul) > 500000/speed){ // Convert speed in steps per second to minimum time between steps. Real minimum step length is whatever this is plus 8 (in microseconds).
        stage = 0;
        pos += (curdir ? 1 : -1); // Ternary. If current direction is true (forwards), add one to position. If current direction is false (backwards), subtract one from position.
        // This caused an issue when, confronted with a negative goal, it went on forever: because position was increasing away from goal, rather than decreasing to it.
      }
    }
}; // This class is very minimal. It doesn't have the charm (and extra logic) of AccelStepper, but I hope we will build on it.