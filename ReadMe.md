# Conway's Game of Life: Now in Color! 

The intent of this project was simple: learn to use CMAKE, and practice C++.

## Features

Beyond your normal GoL project, I added colors with the following rules:  

1) If the cell would Live, then average the color values around the cell.
2) If the cell falls below a certain brightness (addition of the RGB values of the cell) then it cannot produce offspring.
3) There is a random chance for a cell to "mutate" and one of it's colors will turn to full brightness (value of 255).

## Tools

There are some tools that I've included with the program. You can pause the simulation with `space`, step through the next iteration with `right arrow`, and draw new cells with `left click`. The colors are randomized each click, and clicking on a live cell kills it. `Up arrow` and `down arrow` increase and decrease the simulation speed. You can also `right click` on a cell to see it's current RGB values.

## Dependencies

After I learned how to build with CMake properly, unlike with LandGen, you only need to change the CMake file to your install directory of SFML, as well as ensuring the CMake commands work with your version of SFML, in order to compile it yourself.
