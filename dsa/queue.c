#include <stdio.h>

int max = 10;
int front = -1;
int rear = -1;

int ENQ(int Q[], int item) {
	if (rear == max-1) {
		printf("Queue FULL");
		return -1;
	}
	if (front == -1 && rear == -1) {
		front = 0;
		Q[++rear] = item;
	}
	else {
		Q[++rear] = item;
	}
}


int DEQ(int Q[]) {
	if (front == -1) {
		printf("Queue EMPTY");
		return -1;
	}
	int item = Q[front];
	if (front == rear) {
		front = -1;
		rear = -1;
	}
	else {
		front += 1;
	}
	
	return item;
}

void display(int Q[]) {

	for (int i = 0; i < max; i++) {
		printf("%d ", Q[i]);
	}
}

void main() {
	
	int Q[max];
	int n;
	
	do {

		printf("Enter option:\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
		scanf("%d", &n);
		
		if (n==1) {
			printf("Enter item: ");
			int item;
			scanf("%d", &item);
			ENQ(Q, item);
		}
		
		if (n==2) {
			printf("Dequeued item is %d\n", DEQ(Q));
		}
		
		if (n==3) {
			display(Q);
		}
		
	}while(n!=4);

}
