#include <stdio.h>

int TOP = -1;
int maxlen = 10;

// PUSH function
int push(int array[], int value){

	if (TOP == maxlen-1) {

		printf("STACK OVERFLOW\n");
		return 1;
	}
	array[++TOP] = value;
	return 0;
}

// POP function
int pop(int array[]) {

	if (TOP < 0) {
		printf("STACK UNDERFLOW\n");
		return -1;
	}

	int item = array[TOP--];
	return item;
}

// PEEK Function
int peek(int array[]) {

	if (TOP < 0) {
		printf("STACK UNDERFLOW\n");
		return 1;
	}
	printf("%d\n", array[TOP]);
	return 0;
}


// Main function
int main() {

	int base_arr[maxlen];

	push(base_arr, 1);
	peek(base_arr);
	push(base_arr, 2);
	peek(base_arr);
	pop(base_arr);
	pop(base_arr);
	pop(base_arr); // Error demo case
	
	return 0;
}

