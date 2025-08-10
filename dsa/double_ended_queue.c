#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int deque[SIZE];
int front = -1, rear = -1;

int isFull() {
    return (front == 0 && rear == SIZE - 1) || (front == rear + 1);
}

int isEmpty() {
    return front == -1;
}

void enqueueFront(int value) {
    if (isFull()) {
        printf("Deque is full. Cannot insert at front.\n");
        return;
    }

    if (isEmpty()) {
        front = rear = 0;
    } else if (front == 0) {
        front = SIZE - 1;
    } else {
        front--;
    }

    deque[front] = value;
    printf("Inserted %d at front.\n", value);
}

void enqueueRear(int value) {
    if (isFull()) {
        printf("Deque is full. Cannot insert at rear.\n");
        return;
    }

    if (isEmpty()) {
        front = rear = 0;
    } else if (rear == SIZE - 1) {
        rear = 0;
    } else {
        rear++;
    }

    deque[rear] = value;
    printf("Inserted %d at rear.\n", value);
}

void dequeueFront() {
    if (isEmpty()) {
        printf("Deque is empty. Cannot delete from front.\n");
        return;
    }

    printf("Deleted %d from front.\n", deque[front]);

    if (front == rear) {
        front = rear = -1;
    } else if (front == SIZE - 1) {
        front = 0;
    } else {
        front++;
    }
}

void dequeueRear() {
    if (isEmpty()) {
        printf("Deque is empty. Cannot delete from rear.\n");
        return;
    }

    printf("Deleted %d from rear.\n", deque[rear]);

    if (front == rear) {
        front = rear = -1;
    } else if (rear == 0) {
        rear = SIZE - 1;
    } else {
        rear--;
    }
}

void display() {
    if (isEmpty()) {
        printf("Deque is empty.\n");
        return;
    }

    printf("Deque elements: ");
    int i = front;
    while (1) {
        printf("%d ", deque[i]);
        if (i == rear)
            break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    int choice, value;

    while (1) {
        printf("1. Input restricted\n");
        printf("2. Output restricted\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            	
            	int irchoice;
            	
                printf("1. Enqueue\n2. Dequeue (Rear)\n3. Dequeue (Front)\n4. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &irchoice);
                
                switch (irchoice) {
                	case 1:
                		printf("Enter value to enqueue: ");
                		scanf("%d", &value);
                		enqueueRear(value);
                		break;
                		
                	case 2:
                		dequeueRear();
                		break;
                		
                	case 3:
                		dequeueFront();
                		break;
  
                	case 4:
                		exit(0);
                }	
                break;
            case 2:
            	int orchoice;
            	
                printf("1. Enqueue (Front)\n2. Enqueue (Rear)\n3. Dequeue\n4. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &orchoice);
                
                switch (orchoice) {
                	case 1:
                		printf("Enter value to enqueue: ");
                		scanf("%d", &value);
                		enqueueFront(value);
                	
                	case 2:
                		printf("Enter value to enqueue: ");
                		scanf("%d", &value);
                		enqueueRear(value);
                	case 3:
                		dequeueFront();
                		break;
                break;
            case 3:
                dequeueFront();
                break;
            case 4:
                dequeueRear();
                break;
            case 5:
                display();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

