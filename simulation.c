/* Helper function */
void swap(char* a, char* b) {
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

/* Takes a matrix and applies a physics step to the 'blocks'
 * represented by 'solid'
 */
int matrixFallStep(char** matrix, int width, int height, char solid) {
	/* bottom-up traversal */
	for (int row  = height - 2; row >= 0; row--) { // don't run physics on bottom row
		/* left-right traversal */
		for (int col = 0; col < width; col++) {
			if (matrix[row][col] == solid) {
				// down
				if (matrix[row + 1][col] != solid) {
					swap(&matrix[row+1][col], &matrix[row][col]);
				// left
				} else if (col != 0 && matrix[row+1][col-1] != solid){
					swap(&matrix[row+1][col-1], &matrix[row][col]);
				// right
				} else if (col != width - 1 && matrix[row+1][col+1] != solid) {
					swap(&matrix[row+1][col+1], &matrix[row][col]);
				}
			}
		}
	}
	return 0;
}

/* ConsiderimatrixFallStepng a column-based approach to the fall-step...
 * Take the entire column and check if has any "gaps" until the bottom
 * (gaps can be below or within the column)
 * Need to be able to split processing to the columns that have reached the bottom even if
 * There's another column above it
 * Considering a function that can take a column and move it's elements as needed
 * Plan:
 * 	- parse the matrix to identify all columns
 *	- columns that haven't reached the bottom should be moved lower
 * 	- colummns that have reached the bottom should be processed for sliding
 * 	- it's looking like every step will require parsing each column *once*
 * 	- splitting the column into 'sub-columns'
 * 	- apply physics to sub-columns
 */

int advMatrixFallStep(char** matrix, int width, int height, char solid) {
	// parse matrix for vertical lines
	for (int column = 0; column < width; column++) {
		int isSolid = 0;
		int startIdx = -1;
		int endIdx = -1;
		for (int row = 0; row < height; row++) {
			if (matrix[row][column] == solid) {
				if (isSolid == 1) {
					endIdx = row;
				} else {
					startIdx = row;
				}
			} else {
				if (isSolid == 1) {
					isSolid = 0;
					// push sub-column into queue
					// unimplemented
				}
			}
		}

	}

	return 0;
}

/* IMPORTANT:
 * Realising that a state can't be processed using its components
 * The state must be processed as a whole.
 * Processing a queue of components is not viable
 */
