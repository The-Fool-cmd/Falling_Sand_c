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
		matrix[i] = (char*) calloc(width + 1, sizeof(char));
		for (int j = 0; j < width; j++) {
			matrix[i][j] = ' ';
		}
		matrix[i][width] = '\0';
		// fprintf(stderr, "Row length is: %d", strlen(matrix[i]));
	}
	return matrix;
}

/* Like createLine but modifies an existing row of a matrix */
int setLine(char** matrix, int row, int left, int right, char fill, char empty) {
	int length = strlen(matrix[row]);
	if (left > right) {
		perror("Invalid 'left'/'right' parameters!");
		return 1;
	} else if (right > length) {
		perror("'right' is larger than row length");
		return 1;
	}
	for (int idx = 0; idx < left; idx++) {
		matrix[row][idx] = empty;
	}
	for (int idx = left - 1; idx < right; idx++) {
		matrix[row][idx] = fill;
	}
	for (int idx = right; idx < length; idx++) {
		matrix[row][idx] = empty;
	}
	return 0;
}

/* Should set every elem of the provided matrix to 'c' */
int setMatrix(char** matrix, int width, int height, char fill, char empty) {
	// debug: line setting
  for (int i = 0; i < height; i++) {
 		setLine(matrix, i, 0, width, fill, empty);
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

int initTerminal(int fg_color, int bg_color) {
	initscr();
  noecho();
  cbreak(); // disables line buffering
  curs_set(0); // invisible cursor
  nodelay(stdscr, TRUE);

  if (has_colors() == false) {
      endwin();
      printf("Your terminal doesn't support colours.\n");
      return 1;
  }
  // color handling
  start_color();
  init_pair(1, fg_color, bg_color);
  attron(COLOR_PAIR(1));
  return 0;
}

int killTerminal() {

	attroff(COLOR_PAIR(1));
  //printf("Control key is: %c\n", control);
  endwin();
	return 0;
}

int hello_world() {
	initTerminal(COLOR_MAGENTA, COLOR_BLACK);

  int maxX = 0, maxY = 0;
  maxX = getmaxx(stdscr);
  maxY = getmaxy(stdscr);

  char** terminalMatrix = allocateTerminalMatrix(maxX, maxY);

  setMatrix(terminalMatrix, maxX, maxY, 'Y', '.');
  // debug: terminal update via matrix
  updateTerminal(terminalMatrix, maxX, maxY);

  // ncurses cleanup function
  killTerminal();
  free(terminalMatrix);
  return 0;
}
