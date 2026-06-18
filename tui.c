#include <ncurses.h>
#include <stdbool.h>

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

  int y,x;
  x = getmaxx(stdscr);
  y = getmaxy(stdscr);
  x /= 2;
  y /= 2;
  mvprintw(y, x, "Hello World!");
  mvprintw(y+1, x, "Hello World!");
  refresh();

  attroff(COLOR_PAIR(1));

  getch();

  endwin();

  return 0;
}
