
/*class Debugger{
  Motor* xmotor;
  Motor* ymotor;
  
}*/

bool debugMode(LightsController lights){ // Debugging mode. Activates if the command "debug" is sent from a computer.
  if (Serial.available()){
    String data = Serial.readString();
    Serial.println(data);
    /*if (data.substring(0,5) == "xmove"){
      xmotor.move(data.substring(6).toInt());
    }
    else if (data.substring(0, 5) == "ymove"){
      ymotor.move(data.substring(6).toInt());
      Serial.println("Request acknowledged.");
    }
    else if (data.substring(0, 6) == "xspeed"){
      xmotor.setSpeed(data.substring(7).toInt());
    }
    else if (data.substring(0, 6) == "yspeed"){
      ymotor.setSpeed(data.substring(7).toInt());
    }
    else if (data.substring(0, 5) == "yzero"){
      ymotor.zeroTwo(400, &ymotorTwo);
    }
    else */if (data.substring(0, 4) == "exit"){
      return false;
    }
    else if (data.substring(0, 10) == "testLights"){/*
      lights.control(SAY_CHANT_O);
      lights.waitUntilFinished();
      lights.control(SAY_CHANT_X);
      lights.waitUntilFinished();
      lights.control(SAY_CHANT_TIE);*/
    }
  }
  //xmotor.run();
  //ymotor.run();
  return true;
}
