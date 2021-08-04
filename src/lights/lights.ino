Serial coms(13, 14);

void setup(){
  
}

void loop(){
  char data = coms.read();
  if (data == 1){
    coms.write(1);
  }
  else if (data == 2){
    char chant = coms.read();
    if (chant == 0){ // O - A white flashing O
      
    }
    else if (chant == 1){ // X - A white flashing x
      
    }
    else if (chant == 2){ // Starting chant - RGBBRGGBR layout, all ticking down (turning off along the circle
      
    }
    else if (chant == 3){ // Error - All red and flashing
      
    }
    else if (chant == 4){ // Debug mode - All blue and flashing
      
    }
  }
}
