#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "tui.h"
#include "simulation.h"

#define EMPTY '.'
#define SOLID '@'
#define QUIT 'q'
#define STEP 's'

/* Main control code for the entire program
 * Handles communication with the terminal via tui.c
 * Simulation handled by simulation.c
 */

int main() {
	initTerminal(COLOR_MAGENTA, COLOR_BLACK);

	int maxX = 0, maxY = 0;
  maxX = getmaxx(stdscr);
  maxY = getmaxy(stdscr);

  char** terminalMatrix = allocateTerminalMatrix(maxX, maxY);
  setMatrix(terminalMatrix, maxX, maxY, EMPTY, EMPTY);
  setLine(terminalMatrix, 0, 15, maxX-5, SOLID, EMPTY);

	updateTerminal(terminalMatrix, maxX, maxY);

  char control = ' ';
  while(control != QUIT) {
  	control = getch();
   	if (control == STEP) {
	   	matrixFallStep(terminalMatrix, maxX, maxY, SOLID);
			updateTerminal(terminalMatrix, maxX, maxY);
    }
  }
  // Termination procedure
  killTerminal();
  free(terminalMatrix);
	return 0;
}
