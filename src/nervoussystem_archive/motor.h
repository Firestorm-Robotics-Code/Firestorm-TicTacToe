/* By Tyler Clarke
 * Code to control a two-wire stepper motor
 */

// This is an alternative to AccelStepper, which will be specifically tailored to our needs. We will use this instead as it is less than 100 lines and very effecient - It worked on the first try (after I corrected a few type errors and included arduino.h)

// Need to verify that this code works

class Motor;

class Motor{ // Reserve the class name Motor. Redefinition will wonk.
  public:
    long pos = 0; // Long allows for very large position values, with a signed 32 bits. If it seems small, consider how long you could live on 2 billion dollars. (hint: you could spend 1000 dollars a day for around five thousand five hundred years - from the biblical start of the universe to Shakespearean times. You could buy Moses a yacht to make his journey across the ocean easier, and then get front row seats to Hamlet. 
    
    long goal = 0; // Same
    
    boll curdir = false; // Bool (boll) is the most effecient type because it theoretically only uses 1 bit. I'm not sure how this plays out as far as memory is concerned, but it at least uses less space than the barbarous 16-bit integer.

    int dirpin; 
    
    int pulpin;
    
    int stage = 0;

    long lastRamped = 0;
    
    unsigned long reqSpeed = 1000; // Speed is in steps per second.
    unsigned long curSpeed = 0;
    unsigned long oldSpeed = 0;
    
    unsigned long lastMicrosPul = 0; // Last microseconds value for the pulse. Unsigned long is the return type of the micros function.
    
    unsigned long lastMicrosDir = 0; // Last microseconds value for the direction

    boll zero_doing = false;
    boll zero_isAlwaysOn = false;
    int zero_triggerpin = 0;
    int zero_triggerpin_auxillary = 0;
    boll usesAuxSwitch = false;
    boll zero_direction = false;

    boll enabled = true;

    int maxpos;
    int doops = 0;

    boll hasSlave = false;
    boll metrics = false;
    Motor* slave;

    Motor(){ // This is a spoof motor which will not run.
      enabled = false;
    }
    
    Motor(int pul, int dir, bool zero_alwayson, int zero_port, bool zero_dir, int maxPos = -1){ // Zeroing information is included here, so the zero function doesn't need to take arguments. (Except speed, which should be set at runtime not at define time)
      maxpos = maxPos;
      dirpin=dir;
      pulpin=pul;
      pinMode(pul,OUTPUT);
      pinMode(dir,OUTPUT);
      pinMode(zero_port, INPUT_PULLUP);
      zero_isAlwaysOn = zero_alwayson;
      zero_triggerpin = zero_port;
      zero_direction = zero_dir;
    }

    void enableMetrics(){
      metrics = true;
    }

    void setSlave(Motor *theDude){
      slave = theDude;
      hasSlave = true;
    }

    bool isFinished(){
      return (pos == goal) && (hasSlave ? slave -> isFinished() : true); // This is and-exclusion. If we have no slave, there is no reason to have an and, and we simply ignore it by making it "&true".
    }
    
    void stepTasks(int theSpeed, bool direction){ // This simply steps given a speed and direction. Zero and Run (and runSpeed, and runUntil, and runFor) will use this.
      if (not enabled){
        return;
      }
      
      if (curSpeed != theSpeed && millis() > lastRamped + 15){
        curSpeed += theSpeed/abs(theSpeed);
        lastRamped = millis();
      }
      
      if (direction == false && curdir == true){ // Boolean curdir value True = forwards, False = backwards.
        curdir = false; // Flip it back, to the right value.
        digitalWrite(dirpin, HIGH); // This may be backwards - To any other coders who catch this: if this is actually reversed, just flip the "LOW" to "HIGH". This should reverse the direction that it considers "backwards".
      }
      
      if (direction == true && curdir == false){ // These are flipped deliberately. The idea of these if conditions is to catch any situation in which they are wrong.
        curdir = true;
        digitalWrite(dirpin, LOW); // If the other one was backwards, make this one LOW, to reverse the direction.
      }

      // The above if conditions may cause a problem with the direction flipping too soon before the pulse. This could result in the motors driving one step too far - if this becomes an issue, we may have to add a pause of five microseconds after this. For more information: https://cdn.automationdirect.com/static/manuals/leadshinestepper/dm322e.pdf. You can also find that link in the githubs README.md. I used page 13 mostly.

      if (stage == 2 && (micros() - lastMicrosPul) > 500000/curSpeed){ // Convert speed in steps per second to minimum time between steps. Real minimum step length is whatever this is plus 8 (in microseconds).
        stage = 0;
        pos += curdir ? 1 : -1; // Ternary. If current direction is true (forwards), add one to position. If current direction is false (backwards), subtract one from position.
        // This caused an issue when, confronted with a negative goal, it went on forever: because position was increasing away from goal, rather than decreasing to it.
      }

      if (isFinished()){
        curSpeed = 0;
      }
      
      if (stage == 1 && (micros() - lastMicrosPul) >= 8){ // Minimum pulse width of 7.5 μs (microseconds). Half a microsecond is about 1/1500000th of the time it takes to load the google search results about the microsecond symbol, so I decided to just round up to 8 microseconds.
        digitalWrite(pulpin, LOW);
        lastMicrosPul = micros(); // Update the value, so we can keep the pulse "low" until another pulse is needed.
        stage = 2;
      }
      
      if (stage == 0){
        digitalWrite(pulpin, HIGH);
        lastMicrosPul = micros(); // Get the number of microseconds since start of the Arduino. Because MKRZero (the board we're emulating) has a 48 MHZ processor, this should return an absolute value.
        stage = 1;
      } // "If" conditions are in reverse order (stage 2 and down, as opposed to stage 0 and down) as a speed improvement: without it, the micros function will end up being called twice quite often, delaying the system. Because of the 45 megaherts processor, I don't really care about this, but its still good to be efficient.
    }

    bool zeroTasks(int zerospeed){
      if (metrics){
        Serial.println("Running zero tasks");
      }
      if (enabled){
        bool running = true;
        if ((!digitalRead(zero_triggerpin) == zero_isAlwaysOn) && (usesAuxSwitch ? (digitalRead(zero_triggerpin_auxillary) == zero_isAlwaysOn) : true)){
          curdir = !zero_direction;
          stepTasks(zerospeed, zero_direction);
          return false;
        }
        else{
          digitalWrite(dirpin, LOW); // At first you might think this should be -zero_direction, but remember that its always LOW when the motor boots up!
          // Obviously, "zero" should block the thread.
          pos = 0;
          goal = 0;
          return true;
        }
      }
      else{
        return false;
      }
    }

    void lubricate(int lubespeed, long time, int startPos, int distance){
      setGoal(startPos);
      long i = 0;
      while (i < time){
        if (pos <= startPos){
          setGoal(startPos + distance);
          i++;
        }
        if (pos >= startPos + distance){
          setGoal(startPos);
        }
        setGoal(startPos);
        run();
      }
    }

    void zero(int zerospeed){
      if (hasSlave){
        zeroTwo(zerospeed, slave);
      }
      else{
        while (!zeroTasks(zerospeed));
      }
    }

    void zeroTwo(int zerospeed, Motor *motor){ // This is mostly theoretical. It can zero two motors, but it might not hardware fault if it detects one.
      // I am reasonably confident that it will work, but even so, we should be careful and plan for the situation that this doesn't work.
      bool timingOff = false;
      long theTime = 0;
      bool running1 = true;
      bool running2 = true;
      bool running = true;

      int timeoutPoint = 500;
      
      while (running){
        if (!(running1 || running2)){
          running = false;
        }
        if (running1){
          if (zeroTasks(zerospeed)){
            if (timingOff){
              if (millis() < (theTime + timeoutPoint)){
                running = false;
              }
            }
            else{
              running1 = false;
              timingOff = true;
              theTime = millis();
            }
          }
        }
        if (running2){
          if (motor -> zeroTasks(zerospeed)){
            if (timingOff){
              if (millis() < (theTime + timeoutPoint)){
                running = false;
              }
            }
            else{
              running2 = false;
              timingOff = true;
              theTime = millis();
            }
          }
        }
        if (timingOff && !(millis() < (theTime + timeoutPoint))){
          while(!Serial);
          Serial.println("HARDWARE FAULT DETECTED - Either the slides are damaged beyond safe self-repair, or the limit switches are damaged. Location of the fault: motor.h::Motor::zeroTwo::while.0::if.3. IF the issue seems to be because the slides are crooked, and you have not already followed these instructions, simply power down the system and manually zero them, remove any obstructions on the slide path, then restart.");
          while(1);
        }
      }
    }
    
    long getDistance(){ // Return the distance to the goal
      return goal - pos;
    }
    
    void setSpeed(unsigned long newspeed){
      reqSpeed=newspeed;
      oldSpeed = newspeed;
      if (hasSlave){
        slave -> setSpeed(newspeed);
      }
      if (metrics){
        Serial.print("Set speed to ");
        Serial.println(newspeed);
      }
    }
    
    void setGoal(long newgoal){
      goal = newgoal;
      reqSpeed = oldSpeed;
      if (hasSlave){
        slave -> setGoal(newgoal);
      }
    }
    
    void move(int distance){
      goal += distance;
      reqSpeed = oldSpeed;
      if (hasSlave){
        slave -> move(distance);
      }
    }

    void abort(){ // Hard abort. Will eventually pulse motor controller disable pin, for now just performs software disable.
      pos = 0;
      goal = 0;
      enabled = false;
    }
    
    void run(int runSpeed = 0){ // 20 microsecond pulse
      if (metrics){
        Serial.println("Running");
      }
      long distance = getDistance();
      if (hasSlave){
        slave -> run(runSpeed); // Run the slave. This assumes that the slave is running the same direction, so it might be dangerous.
      }
      if (runSpeed == 0){
        stepTasks(curSpeed, distance > 0); // We know that getDistance will always be negative or positive, never zero, because of the if condition.
        if ((curSpeed != reqSpeed) && (millis() > 30)){ // Slow, 45-degree ramp.
          lastRamped = millis();
          curSpeed += reqSpeed / abs(reqSpeed);
        }
        if (stage == 0){ // If stage is zero, the pin is high. This could be an issue, potentially.
          pos += distance/abs(distance);
        }
        if (distance == 0){
          curSpeed = 0;
          reqSpeed = 0;
        }
      }
      else{
        stepTasks(runSpeed, runSpeed > 0); // Runspeed won't be equal to 0 either!
      }
    }
}; // This class is very minimal. It doesn't have the charm (and extra logic) of AccelStepper, but I hope we will build on it.
