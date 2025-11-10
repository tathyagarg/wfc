#include <iostream>
#include <cstdlib>

#include "exampleConfig.h"
#include "grid.hpp"

/*
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 */
int main() {
  srand(0);

  Grid grid(3, 3, 4, {
    {0, 3, RIGHT},
    {0, 3, DOWN},
    {0, 3, LEFT},
    {0, 3, UP},
    {0, 1, RIGHT},
    {0, 1, LEFT},
    {0, 2, DOWN},
    {0, 2, UP},
    {1, 2, DOWN},
    {1, 2, UP},
    {2, 1, RIGHT},
    {2, 1, LEFT},
    {1, 3, UP},
    {1, 3, DOWN},
    {2, 3, RIGHT},
    {2, 3, LEFT}
  });

  grid.observe_tile_random(1, 1);
  grid.print_grid();
}
