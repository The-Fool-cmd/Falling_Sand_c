/* Takes a matrix and applies a physics step to the 'blocks'
 * represented by 'solid'
 */
int matrixFallStep(char** matrix, int width, int height, char solid) {
	/* bottom-up traversal */
	for (int row  = height - 2; row >= 0; row--) { // don't run physics on bottom row
		/* left-right traversal */
		for (int col = 0; col < width; col++) {
			// swap solid downwards if possible
			if (matrix[row + 1][col] != solid && matrix[row][col] == solid) {
				char tmp = matrix[row+1][col];
				matrix[row+1][col] = matrix[row][col];
				matrix[row][col] = tmp;
			}
		}
	}
	return 0;
}
