#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Creates a line of given char-s
 * Starting from 'left' index and ending at 'right' index
 * ' ' used as empty chars
 * Returns a pointer to the heap allocated string
 * Caller frees
 */
char* createLine(int length, int left, int right, char c) {
	// + 1 for '\0'
	char* line = (char*) calloc(length + 1, sizeof(char));
	for (int idx = 0; idx < left; idx++) {
		line[idx] = ' ';
	}
	for (int idx = left - 1; idx < right; idx++) {
		line[idx] = c;
	}
	for (int idx = right; idx < length; idx++) {
		line[idx] = ' ';
	}
	line[length] = '\0';
	return line;
}

/* Matrix that spans the entire screen
 * Initialised with ' '-s
 * Caller frees
 */
char** allocateTerminalMatrix(int width, int height){
	char** matrix = (char**) calloc(height, sizeof(char*));
	for (int i = 0; i < height; i++) {
		matrix[i] = (char*) calloc(width, sizeof(char));
		for (int j = 0; j < width; j++) {
			matrix[i][j] = ' ';
		}
		matrix[i][width] = '\0';
		fprintf(stderr, "Row length is: %d", strlen(matrix[i]));
	}
	return matrix;
}

int setLine(char** matrix, int row, int left, int right, char c) {
	int length = strlen(matrix[row]);
	if (left > right) {
		perror("Invalid 'left'/'right' parameters!");
		return 1;
	} else if (right > length) {
		perror("'right' is larger than row length");
		return 1;
	}
	// + 1 for '\0'
	for (int idx = 0; idx < left; idx++) {
		matrix[row][idx] = ' ';
	}
	for (int idx = left - 1; idx < right; idx++) {
		matrix[row][idx] = c;
	}
	for (int idx = right; idx < length; idx++) {
		matrix[row][idx] = ' ';
	}
	return 0;
}

/* Assumes terminal Matrix is not out of bounds vertically */
int updateTerminal(char** terminalMatrix, int maxX, int maxY) {
	for (int i = 0; i < maxY; i++){
 		//setLine(terminalMatrix, i, i+1, maxX -i, 'k');
  	mvprintw(i, 0, "%s", terminalMatrix[i]);
  }
  refresh();
	return 0;
}


int hello_world() {
  initscr();
  noecho();
  // cbreak();
  // keypad(stdscr, true);
  curs_set(0); // cursor appearance

  if (has_colors() == false) {
      endwin();
      printf("Your terminal doesn't support colours.\n");
      return 1;
  }

  start_color();
  //fg & bg colors
  init_pair(1, COLOR_WHITE, COLOR_BLUE);

  attron(COLOR_PAIR(1));

  int maxX = 0, maxY = 0;
  maxX = getmaxx(stdscr);
  maxY = getmaxy(stdscr);
  //fprintf(stderr, "MaxX: %d MaxY: %d", maxX, maxY);
  char** terminalMatrix = allocateTerminalMatrix(maxX, maxY);

  // test line setting and freeing performance
  for (int i = 0; i < maxY; i++) {
 		setLine(terminalMatrix, i, 0, maxX, 'T');
  }
  updateTerminal(terminalMatrix, maxX, maxY);
  refresh();

  attroff(COLOR_PAIR(1));

  getch();

  endwin();
  free(terminalMatrix);
  //printf("MaxX is: %d, line length is: %d\n", maxX, strlen(testString));
  return 0;
}
