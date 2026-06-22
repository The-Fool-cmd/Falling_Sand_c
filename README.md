# Falling_Sand_c

A simple TUI simulation for falling sand, written in C using ncurses.

# Controls:

Solid elements are defined as the '@' character. Can be changed in the master.c macros.

Same for empty elements.

key commands:

- 'q' - quit
- 'p' - pause
- '.' - faster
- ',' - slower

### The initial state is passed as a filename in the argument

Input format is:

`x y` where x is the width, and y is the height of the matrix

`matrix of 1-s and 0-s` where 1-s are 'solid' and 0-s are 'empty

You can modify the state files inside of the project directory if you'd like to experiment.
