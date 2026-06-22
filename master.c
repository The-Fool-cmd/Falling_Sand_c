#include "simulation.h"
#include "tui.h"
#include <bits/time.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Main input code for the entire program
 * Handles communication with the terminal via tui.c
 * Simulation handled by simulation.c
 */

#define EMPTY '.'
#define SOLID '@'
#define QUIT 'q'
#define PAUSE 'p'
#define FASTER '.'
#define SLOWER ','
#define STATE_PAUSED 0
#define STATE_PLAYING 1
#define STATE_QUIT 2

void updateTime(struct timespec *time) { clock_gettime(CLOCK_MONOTONIC, time); }

int sleepUntilNextTick(struct timespec *prevTime,
                       struct timespec *stepDuration) {
  if (stepDuration->tv_nsec == 0 && stepDuration->tv_sec == 0) {
    return 1;
  }
  struct timespec currentTime;
  updateTime(&currentTime);
  struct timespec sleepDuration = {0};
  sleepDuration.tv_sec =
      prevTime->tv_sec + stepDuration->tv_sec - currentTime.tv_sec;
  sleepDuration.tv_nsec =
      prevTime->tv_nsec + stepDuration->tv_nsec - currentTime.tv_nsec;
  if (sleepDuration.tv_nsec < 0) {
    sleepDuration.tv_sec--;
    sleepDuration.tv_nsec += 1000000000L;
  }
  if (sleepDuration.tv_sec >= 0)
    nanosleep(&sleepDuration, NULL);
  updateTime(prevTime);
  return 0;
}

void updateStepDuration(float speed, struct timespec *stepDuration) {
  float interval = 1.0f / speed;
  stepDuration->tv_sec = (time_t)interval;
  stepDuration->tv_nsec = (long)((interval - stepDuration->tv_sec) * 1e9f);
}
/* Updates the state given using provided input */
int updateStateAndSpeed(int8_t *state, float *speed,
                        struct timespec *stepDuration, char *input) {
  switch (*input) {
  case (QUIT): {
    *state = STATE_QUIT;
    break;
  }
  case (PAUSE): {
    *state = *state == STATE_PAUSED ? STATE_PLAYING : STATE_PAUSED;
    break;
  }
  case (FASTER): {
    *speed = *speed < 10 ? *speed + 1 : 20;
    updateStepDuration(*speed, stepDuration);
    break;
  }
  case (SLOWER): {
    *speed = *speed > 1 ? *speed - 1 : 1;
    updateStepDuration(*speed, stepDuration);
    break;
  }
  }
  return 0;
}

int getInitialStateFromFile(int32_t maxX, int32_t maxY, char **matrix,
                            char *filename, char solid, char empty) {
  FILE *f = fopen(filename, "r");
  if (!f)
    return 1;

  int32_t patW, patH;
  if (fscanf(f, "%d %d\n", &patW, &patH) != 2) {
    fclose(f);
    return 1;
  }

  if (patW > maxX || patH > maxY) {
    fclose(f);
    return 2;
  }

  setMatrix(matrix, maxX, maxY, empty, empty);

  int32_t colOffset = (maxX - patW) / 2;
  char line[patW + 2];

  for (int row = 0; row < patH && row < maxY; row++) {
    if (!fgets(line, sizeof(line), f))
      break;
    for (int col = 0; col < patW && colOffset + col < maxX; col++) {
      matrix[row][colOffset + col] = (line[col] == '1') ? solid : empty;
    }
  }

  fclose(f);
  return 0;
}

int main(int argc, char **argv) {
  int32_t maxX = 0, maxY = 0;
  float speed = 1; // speed is in FPS/TPS
  int8_t state = STATE_PAUSED;
  char input = ' ';
  struct timespec prevTime = {0};
  struct timespec stepDuration = {0};
  initTerminal(COLOR_MAGENTA, COLOR_BLACK);

  maxX = getmaxx(stdscr);
  maxY = getmaxy(stdscr);

  char **terminalMatrix = allocateTerminalMatrix(maxX, maxY);

  updateStepDuration(speed, &stepDuration);

  /* SET INITIAL SIMULATION STATE */
  char *filename = argc > 1 ? argv[1] : "state_default.txt";
  int loadResult = getInitialStateFromFile(maxX, maxY, terminalMatrix, filename,
                                           SOLID, EMPTY);
  if (loadResult != 0) {
    killTerminal();
    free(terminalMatrix);
    if (loadResult == 2)
      printf("Error: '%s' is too large for the current terminal (%dx%d)\n",
             filename, maxX, maxY);
    else
      printf("Error: could not open state file '%s'\n", filename);
    return 1;
  }
  updateTerminal(terminalMatrix, maxX, maxY);

  updateTime(&prevTime);
  /* MAIN SIMULATION LOOP */
  while (state != STATE_QUIT) {
    input = getch();
    updateStateAndSpeed(&state, &speed, &stepDuration, &input);
    input = ' ';
    if (state == STATE_PLAYING) {
      matrixFallStep(terminalMatrix, maxX, maxY, SOLID);
      updateTerminal(terminalMatrix, maxX, maxY);
    }
    sleepUntilNextTick(&prevTime, &stepDuration);
  }
  // Termination procedure
  killTerminal();
  for (int i = 0; i < maxY; i++)
    free(terminalMatrix[i]);
  free(terminalMatrix);
  return 0;
}
