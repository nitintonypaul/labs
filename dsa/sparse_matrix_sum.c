#include <stdio.h>
#include <stdlib.h> 


#define MAX_TERMS 10


typedef struct {
    int row;
    int col;
    int value;
} SparseElement;


void createSparseMatrix(SparseElement matrix[]) {
    int numRows, numCols, numNonZero;

    printf("Enter total number of rows: ");
    scanf("%d", &numRows);

    printf("Enter total number of columns: ");
    scanf("%d", &numCols);

    printf("Enter total number of non-zero elements: ");
    scanf("%d", &numNonZero);

    if (numNonZero > MAX_TERMS) {
        printf("Number of non-zero elements exceeds the maximum of %d.\n", MAX_TERMS);
        matrix[0].value = 0; 
        return;
    }

    
    matrix[0].row = numRows;
    matrix[0].col = numCols;
    matrix[0].value = numNonZero;

    printf("Enter the non-zero elements (row, column, value) in sorted order:\n");
    
    for (int i = 1; i <= numNonZero; i++) {
        scanf("%d %d %d", &matrix[i].row, &matrix[i].col, &matrix[i].value);
    }
}


void displaySparseMatrix(const SparseElement matrix[]) {
    int numNonZero = matrix[0].value;
    if (matrix[0].row <= 0 || matrix[0].col <= 0) return;

    for (int i = 1; i <= numNonZero; i++) {
        printf("%d\t%d\t%d\n", matrix[i].row, matrix[i].col, matrix[i].value);
    }
}


void addSparseMatrices(const SparseElement m1[], const SparseElement m2[], SparseElement result[]) {
    
    if (m1[0].row != m2[0].row || m1[0].col != m2[0].col) {
        printf("\nMatrices cannot be added. Dimensions are different.\n");
        result[0].row = 0; 
        result[0].col = 0;
        result[0].value = 0;
        return;
    }

    
    result[0].row = m1[0].row;
    result[0].col = m1[0].col;
    
    int i = 1; 
    int j = 1; 
    int k = 1; 

    while (i <= m1[0].value && j <= m2[0].value) {
        if (m1[i].row < m2[j].row) {
            result[k++] = m1[i++];
        } 
		else if (m1[i].row > m2[j].row) {
            result[k++] = m2[j++];
        } 
		else { 
            
			if (m1[i].col < m2[j].col) {
                result[k++] = m1[i++];
            }

			else if (m1[i].col > m2[j].col) {
                result[k++] = m2[j++];
            }

			else { 
                int sum = m1[i].value + m2[j].value;
                if (sum != 0) {
                    result[k].row = m1[i].row;
                    result[k].col = m1[i].col;
                    result[k].value = sum;
                    k++;
                }
                i++;
                j++;
            }
        }
    }

    while (i <= m1[0].value) {
        result[k++] = m1[i++];
    }

    while (j <= m2[0].value) {
        result[k++] = m2[j++];
    }

    result[0].value = k - 1;
}

int main() {
    SparseElement matrix1[MAX_TERMS + 1];
    SparseElement matrix2[MAX_TERMS + 1];
    SparseElement sumMatrix[MAX_TERMS * 2 + 1]; 

    printf("\nEnter details for the first sparse matrix:\n");
    createSparseMatrix(matrix1);

    printf("\nEnter details for the second sparse matrix:\n");
    createSparseMatrix(matrix2);

	printf("\nMatrix 1\n");
    displaySparseMatrix(matrix1);
	printf("\nMatrix 2\n");
    displaySparseMatrix(matrix2);

    addSparseMatrices(matrix1, matrix2, sumMatrix);

    if (sumMatrix[0].row > 0) {
        printf("\nSum");
        displaySparseMatrix(sumMatrix);
    }
    
    return 0;
}