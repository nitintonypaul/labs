#include <stdio.h>

// constants
int TOP = -1;
int maxlen = 10;

// PUSH function
int push(char array[], char value){

	if (TOP == maxlen-1) {

		printf("STACK OVERFLOW\n");
		return 1;
	}
	array[++TOP] = value;
	return 0;
}

// POP function
char pop(char array[]) {

	if (TOP < 0) {
		printf("STACK UNDERFLOW\n");
		return '!';
	}

	char item = array[TOP--];
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

int main() {
	
	// dual arrays
	char str[maxlen];
	char stack[maxlen];
	
	// obtaining a string
	printf("Enter a string: ");
	scanf("%s", &str);
	
	// pushing into stack
	for (int i = 0; i < maxlen; i++){
		push(stack, str[i]);
	}
	
	// popping out of stack
	for (int i = 0; i < maxlen; i++) {
		printf("%c", pop(stack));
	}
	
	printf("\n");
	
	return 0;
}
