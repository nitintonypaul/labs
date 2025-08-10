#include <stdio.h>

struct term {
	int row;
	int col;
	int val;
};

void main() {

	int row;
	int col;
	printf("Enter number of rows and columns for matrix 1:\n");
	scanf("%d%d", &row, &col);
	
	int matrix1[row][col];
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("Enter element of row %d and column %d: ", i, j);
			scanf("%d", &matrix1[i][j]);
		}
	}
	
	int nonzC = 0;
	int sparseCounter = 1;
	struct term sparse1[row+col];	
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (matrix1[i][j] != 0) {
				sparse1[sparseCounter].row = i;
				sparse1[sparseCounter].col = j;
				sparse1[sparseCounter].val = matrix1[i][j];
				sparseCounter++;
				nonzC++;
			}
		}
	}

	sparse1[0].row = row;
	sparse1[0].col = col;
	sparse1[0].val = nonzC;
	
	print("\nSparse Matrix\n");
	for (int i = 0; i <= nonzC; i++) {
		printf("%d  %d  %d\n", sparse1[i].row, sparse1[i].col, sparse1[i].val);	
	}
}
