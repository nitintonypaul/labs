#include <stdio.h>

#include <stdio.h>

int TOP1 = -1;
int TOP2 = 9;
int maxlen = 10;

// PUSH function
int push(int array[], int value, int * TOP){

	if (*TOP == maxlen-1) {

		printf("STACK OVERFLOW\n");
		return 1;
	}
	array[++(*TOP)] = value;
	return 0;
}

// POP function
int pop(int array[], int * TOP) {

	if (*TOP < 0) {
		printf("STACK UNDERFLOW\n");
		return -1;
	}

	int item = array[(*TOP)--];
	return item;
}

int peek(int array[], int * TOP) {
	
	if (*TOP < 0) {
		return -1;
	}
	
	return array[*TOP];
}

void printarr(int arr[]) {

	for (int i = 0; i < maxlen; i++) {
		printf("%d  ", arr[i]);
	}	
	
	printf("\n");
}


void main() {

	int stack_one[] = {1,3,2,4,9,6,5,8,7,0};
	int stack_two[maxlen];
	
	printarr(stack_one);
	
	push(stack_two, pop(stack_one, &TOP1), &TOP2);
	
	while (TOP2 < maxlen-1) {
		
		int countervar = 0;
		int funnyvariable = pop(stack_one, &TOP1);
		if (peek(stack_two, &TOP2) > funnyvariable) {
			push(stack_two, funnyvariable, &TOP2);
			continue;
		}
		
		while (peek(stack_two, &TOP2) > funnyvariable) {
			int temp = pop(stack_two, &TOP2);
			push(stack_one, temp, &TOP1);
			countervar++;
		}
		
		push(stack_two, funnyvariable, &TOP2); 
		
		for (int i = 0; i < countervar; i ++) {
			push(stack_two, pop(stack_one, &TOP1), &TOP2);
		} 
	
	}
	
	printarr(stack_two);

}
