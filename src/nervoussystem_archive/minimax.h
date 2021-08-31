// Workflow: I call function with the type (bool) and the grid (uint8_t[3][3]), it returns an uint8_t[2], the first being x and the second being y.

int8_t equals3(uint8_t a,uint8_t b) {
  return a == b && a != 0;
}

int8_t *okMove(uint8_t **grid) {

  int8_t returner[2];
  returner[0] = random(0, 3);
  returner[1] = random(0, 3);

  // horizontal
  for (int8_t i = 0; i < 3; i++) {
    if (equals3(grid[i][0], grid[i][1])) {
      returner[0] = i;
      returner[1] = 2;
    }
    if (equals3(grid[i][0], grid[i][2])) {
      returner[0] = i;
      returner[1] = 1;
    }
    if (equals3(grid[i][1], grid[i][2])){
      returner[0] = i;
      returner[1] = 0;
    }
  }

  // Vertical
  for (int8_t i = 0; i < 3; i++) {
    if (equals3(grid[0][i], grid[1][i])) {
      returner[0] = 2;
      returner[1] = i;
    }
    if (equals3(grid[0][i], grid[2][i])) {
      returner[0] = 1;
      returner[1] = i;
    }
    if (equals3(grid[1][i], grid[2][i])){
      returner[0] = 0;
      returner[1] = i;
    }
  }

  // Diagonal
  if (equals3(grid[0][0], grid[1][1])) {
    returner[0] = 2;
    returner[1] = 2;
  }
  if (equals3(grid[0][0], grid[2][2])) {
    returner[0] = 1;
    returner[1] = 1;
  }
  if (equals3(grid[2][2], grid[1][1])) {
    returner[0] = 0;
    returner[1] = 0;
  }
  if (equals3(grid[1][1], grid[0][2])) {
    returner[0] = 2;
    returner[1] = 0;
  }
  if (equals3(grid[2][0], grid[0][2])) {
    returner[0] = 1;
    returner[1] = 1;
  }
  if (equals3(grid[1][1], grid[2][0])) {
    returner[0] = 0;
    returner[1] = 2;
  }
  return returner;
}
