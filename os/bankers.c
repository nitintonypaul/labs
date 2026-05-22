#include <stdio.h>

void display_matrix(int rows, int columns, int matrix[rows][columns]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void display_vector(int *vector, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

void max_to_need(int rows, int columns, int allocation[rows][columns], int maximum[rows][columns]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            maximum[i][j] -= allocation[i][j];
        }
    }
}

int can_allocate(int *need, int *available, int length) {
    if (need[0] == -1) return 0;   // already finished
    for (int i = 0; i < length; i++) {
        if (need[i] > available[i]) {
            return 0;
        }
    }
    return 1;
}

void finish_process(int *allocation, int *available, int length) {
    for (int i = 0; i < length; i++) {
        available[i] += allocation[i];   // release allocation, not need
    }
}

int main() {
    int number_of_resources;
    printf("Enter number of resources: ");
    scanf("%d", &number_of_resources);

    int resources[number_of_resources];
    for (int i = 0; i < number_of_resources; i++) {
        printf("Enter quantity of resource %d: ", i);
        scanf("%d", &resources[i]);
    }

    int number_of_processes;
    printf("Enter number of processes: ");
    scanf("%d", &number_of_processes);

    int allocation[number_of_processes][number_of_resources];
    int maximum[number_of_processes][number_of_resources];

    for (int i = 0; i < number_of_processes; i++) {
        printf("Process P%d Input\n----------\n", i);
        for (int j = 0; j < number_of_resources; j++) {
            printf("Enter Allocation of P%d of resource %d: ", i, j);
            scanf("%d", &allocation[i][j]);

            printf("Enter Max of P%d of resource %d: ", i, j);
            scanf("%d", &maximum[i][j]);
        }
    }

    max_to_need(number_of_processes, number_of_resources, allocation, maximum);

    printf("\nNEED MATRIX\n---------------\n");
    display_matrix(number_of_processes, number_of_resources, maximum);

    printf("\nALLOCATION MATRIX\n---------------\n");
    display_matrix(number_of_processes, number_of_resources, allocation);

    printf("\nAVAILABLE VECTOR\n---------------\n");
    display_vector(resources, number_of_resources);

    int remaining = number_of_processes;

    while (remaining > 0) {
        int progressed = 0;

        for (int i = 0; i < number_of_processes; i++) {
            if (can_allocate(maximum[i], resources, number_of_resources)) {
                finish_process(allocation[i], resources, number_of_resources);
                for (int j = 0; j < number_of_resources; j++) {
                    maximum[i][j] = -1;   // mark process finished
                }
                remaining--;
                progressed = 1;
            }
        }

        if (!progressed) {
            break;
        }
    }

    if (remaining == 0) {
        printf("SYSTEM IS IN A SAFE STATE\n");
    } else {
        printf("SYSTEM IS IN AN UNSAFE STATE\n");
    }
}