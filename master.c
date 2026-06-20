#include <ncurses.h>
#include <stdlib.h>
#include "tui.h"
#include "simulation.h"

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


  setMatrix(terminalMatrix, maxX, maxY, 'y');

  updateTerminal(terminalMatrix, maxX, maxY);
  // Blocking call
  getch();

  // Termination procedure
  killTerminal();
  free(terminalMatrix);
	return 0;
}
