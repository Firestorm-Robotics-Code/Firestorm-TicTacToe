/* By Tyler Clarke with help from Lawson Brashear
 * Wrapper around motor.h file which makes the arm move on the grid, pick up tiles, and do a variety of other tasks.
 * 
 * 5x5 grid, in gridsquares
 * 
 * Uses inches, not centimeters - multiply by 2.54
 */


#define TILEWIDTH 1 // One inch tile width for testing.
#define MAXOPS 10 // Ten is the maximum possible grid operations in cache.


class GridOperation{ // Grid Operation, does an Operation on the Grid.
private:
  int8_t gridpos_x;
  int8_t gridpos_y;
  Motor* xmotor;
  Motor* ymotor;
  boolean isFinished;
  uint8_t optype;
public:
  GridOperation(uint8_t operationtype, Motor* x, Motor* y, int8_t gridx, int8_t gridy){
    ymotor = y;
    xmotor = x;
    optype = operationtype;
    isFinished = false;
    gridpos_x = gridx;
    gridpos_y = gridy;
  }
  void start(){
    ymotor.setGoal(gridpos_y * 800 * TILEWIDTH);
    xmotor.setGoal(gridpos_x * 800 * TILEWIDTH);
  }
  bool run(){ // Return true if it is time to toss this GridOperation.
    ymotor.run();
    xmotor.run();
    return ymotor.isFinished() && xmotor.isFinished();
  }
}


class Grid{
private:
  int tilewidth = 0;
  GridOperation[
  uint8_t grid[5][5]={ // 0 = nothing, 1 = "O", 2 = "X"
    {1,1,1,1,1},
    {0,0,0,0,2},
    {0,0,0,0,2},
    {0,0,0,0,2},
    {0,0,0,2,2}
  };
  Motor* xmotor;
  Motor* ymotor;
  
public:
  Grid(Motor *Xmotor, Motor *Ymotor, int twidth){
    xmotor=Xmotor;
    ymotor=Ymotor;
    tilewidth=twidth;
  }
};
