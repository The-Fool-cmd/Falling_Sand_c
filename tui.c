#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Matrix that spans the entire screen
 * Initialised with ' '-s
 * Caller frees
 */
char **allocateTerminalMatrix(int width, int height) {
  char **matrix = (char **)calloc(height, sizeof(char *));
  for (int i = 0; i < height; i++) {
    matrix[i] = (char *)calloc(width + 1, sizeof(char));
    for (int j = 0; j < width; j++) {
      matrix[i][j] = ' ';
    }
    matrix[i][width] = '\0';
  }
  return matrix;
}

/* Like createLine but modifies an existing row of a matrix */
int setLine(char **matrix, int row, int left, int right, char fill,
            char empty) {
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
  for (int idx = left; idx < right; idx++) {
    matrix[row][idx] = fill;
  }
  for (int idx = right; idx < length; idx++) {
    matrix[row][idx] = empty;
  }
  return 0;
}

int setMatrix(char **matrix, int width, int height, char fill, char empty) {
  for (int i = 0; i < height; i++) {
    setLine(matrix, i, 0, width, fill, empty);
  }
  return 0;
}

int updateTerminal(char **terminalMatrix, int maxX, int maxY) {
  for (int i = 0; i < maxY; i++) {
    mvprintw(i, 0, "%s", terminalMatrix[i]);
  }
  refresh();
  return 0;
}

int initTerminal(int fg_color, int bg_color) {
  initscr();
  noecho();
  cbreak();    // disables line buffering
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
  endwin();
  return 0;
}
