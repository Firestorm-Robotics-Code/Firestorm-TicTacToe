/* By Tyler Clarke with help from Lawson Brashear
 * Wrapper around motor.h file which makes the arm move on the grid, pick up tiles, and do a variety of other tasks.
 * 
 * 5x5 grid, in gridsquares
 * 
 * Uses inches, not centimeters - multiply by 2.54
 */


class GridOperation{ // Grid Operation, does an Operation on the Grid.
  
}


class Grid{
private:
  int tilewidth = 0;
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
