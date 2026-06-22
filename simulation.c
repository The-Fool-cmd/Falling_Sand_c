/* Helper function */
void swap(char *a, char *b) {
  char tmp = *a;
  *a = *b;
  *b = tmp;
}

/* Takes a matrix and applies a physics step to the 'blocks'
 * represented by 'solid'
 */
int matrixFallStep(char **matrix, int width, int height, char solid) {
  /* bottom-up traversal */
  for (int row = height - 2; row >= 0;
       row--) { // don't run physics on bottom row
    /* left-right traversal */
    for (int col = 0; col < width; col++) {
      if (matrix[row][col] == solid) {
        // down
        if (matrix[row + 1][col] != solid) {
          swap(&matrix[row + 1][col], &matrix[row][col]);
          // left
        } else if (col != 0 && matrix[row + 1][col - 1] != solid) {
          swap(&matrix[row + 1][col - 1], &matrix[row][col]);
          // right
        } else if (col != width - 1 && matrix[row + 1][col + 1] != solid &&
                   matrix[row][col + 1] != solid) {
          swap(&matrix[row + 1][col + 1], &matrix[row][col]);
        }
      }
    }
  }
  return 0;
}
