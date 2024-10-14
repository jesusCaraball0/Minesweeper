# Minesweeper
## Description
Minesweeper video game implemented using the SFML C++ Library. Includes all necessary functionality, from bomb grid generation to tile discovery and flagging. Game GUI displays clickable grid, flag and bomb counter, and a restart button. The game is played by clicking all the tiles without bombs; the strategy is to figure out where the bombs are based on the numbered tiles. The number on a tile indicates how many bombs are directly around it. 
## Install Instructions
To run the game, install MinGW32 and SFML. Then add, the include and lib SFML folder paths to the Makefile. Run the Makefile using mingw32-make and it should create app.exe, which opens the game when ran.
## Future Contribution Ideas
1. Update board to be dynamic; make the game playable in a different sized grid.
2. Add option to hide debug buttons such as bomb visibility and test grids.
3. Add a game timer for an extra challenge.
