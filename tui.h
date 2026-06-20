/* Handles initialisation of the ncurses TUI */
int initTerminal(int fg_color, int bg_color);
/* Updated the TUI using provided matrix and terminal dimensions */
int updateTerminal(char** terminalMatrix, int maxX, int maxY);
/* Cleans up ncurses TUI. Does NOT end the process */
int killTerminal();
/* Returns a heap-allocated string generated using |...left-"c...c"-right...| */
char* createLine(int length, int left, int right, char c);
/* Returns a pointer to a heap-allocated matrix that spans the entire terminal */
char** allocateTerminalMatrix(int width, int height);
/* Sets the row of a matrix to 'c' using |...left-"c...c"-right...| */
int setLine(char** matrix, int row, int left, int right, char fill, char empty);
/* Sets all elems of the matrix to 'c' */
int setMatrix(char** matrix, int width, int height, char fill, char empty);
/* Debugging function */
int hello_world();
