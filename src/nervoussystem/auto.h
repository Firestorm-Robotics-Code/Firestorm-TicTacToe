/* By Tyler Clarke, originally going to be by Lawson Brashear but he's a wanker.
 *  
 *  Defines a set of functions for simple AI.
 */

void AI_random(uint8_t grid[3][3], bool myColor, uint8_t *returner) {
  returner[0] = random(0, 3);
  returner[1] = random(0, 3);
}

void AI_xkcd(uint8_t grid[3][3], bool myColor, uint8_t *returner) { // Based on the XKCD one (https://xkcd.com/832), thank you for saving my life, Randall Munroe.
  // Oh wait, nvm. Not gonna go through this pain, there must be a better way.
}

void AI_Lawson(uint8_t grid[3][3], bool myColor, uint8_t *returner) { // Lawson-style AI. Only ever blocks.
  
}

void AI_nope(uint8_t grid[3][3], bool myColor, uint8_t *returner) { // Don't use this.
  if (grid[1][1] == 0){
    returner[0] = 1;
    returner[1] = 1;
  }
  else if (grid[0][0] == 0){ // Play the bottom-left corner (top-right to a user)
    returner[0] = 0;
    returner[1] = 0;
  }
  else if (grid[2][2] == 0){
    returner[0] = 2;
    returner[1] = 2;
  }
  else if (grid[2][0] == 0){
    returner[0] = 0;
    returner[1] = 2;
  }
  else if (grid[0][2] == 0){
    returner[0] = 2;
    returner[1] = 0;
  }
  else if (grid[0][1] == 0){
    returner[0] = 1;
    returner[1] = 0;
  }
  else if (grid[1][0] == 0){
    returner[0] = 0;
    returner[1] = 1;
  }
  else if (grid[2][1] == 0){
    returner[0] = 1;
    returner[1] = 2;
  }
  else if (grid[1][2] == 0){
    returner[0] = 2;
    returner[1] = 1;
  }
  else{
    returner[0] = 0;
    returner[1] = 0;
    Serial.println("No possible moves, looks like a tie...");
  }
}
