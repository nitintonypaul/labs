#include <stdio.h>

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

    printf("Enter the non-zero elements (row, column, value):\n");
    
    for (int i = 1; i <= numNonZero; i++) {
        scanf("%d %d %d", &matrix[i].row, &matrix[i].col, &matrix[i].value);
    }
}


void displaySparseMatrix(const SparseElement matrix[]) {
    int numNonZero = matrix[0].value;
    
    for (int i = 1; i <= numNonZero; i++) {
        printf("%d\t%d\t%d\n", matrix[i].row, matrix[i].col, matrix[i].value);
    }
}


void transposeSparseMatrix(const SparseElement original[], SparseElement transpose[]) {
    
    int numRows = original[0].row;
    int numCols = original[0].col;
    int numTerms = original[0].value;

    
    transpose[0].row = numCols;    
    transpose[0].col = numRows;    
    transpose[0].value = numTerms; 

    if (numTerms == 0) {
        return; 
    }

    int current_pos = 1; 

    
    for (int c = 0; c < numCols; c++) {
        
        for (int i = 1; i <= numTerms; i++) {
            
            if (original[i].col == c) {
                
                transpose[current_pos].row = original[i].col;
                transpose[current_pos].col = original[i].row;
                transpose[current_pos].value = original[i].value;
                current_pos++;
            }
        }
    }
}

int main() {
    
    SparseElement original[MAX_TERMS + 1];
    SparseElement transpose[MAX_TERMS + 1];

    printf("Enter details for the original sparse matrix:\n");
    createSparseMatrix(original);
    displaySparseMatrix(original);
    transposeSparseMatrix(original, transpose);
    displaySparseMatrix(transpose);

    return 0;
}