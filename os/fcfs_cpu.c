#include <stdio.h>

struct request {
    int id;
    int arrival_time;
    int execution_time;
};

void enqueue(struct request *q, struct request val, int *back) {
    q[(*back)++] = val;
}

struct request dequeue(struct request *q, int *front) {
    return q[(*front)++];
}

struct request peek(struct request *q, int front) {
    return q[front];
}

void bubble_sort(struct request *arr, int n) {
    for (int i = 0; i < n - 1; i++) {

        int swapped = 0;

        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j].arrival_time > arr[j + 1].arrival_time) {
                struct request temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }
}

void main() {

    // Obtaining number of requests
    int n;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    
    // Request queue
    struct request request_arr[n];
    int front = 0;
    int back = 0;

    // Obtaining requests
    for (int i = 0; i < n; i++) {
        int at, et;
        printf("Enter arrival time of P%d: ", i);
        scanf("%d", &at);
        printf("Enter execution time of P%d: ", i);
        scanf("%d", &et);

        struct request temp;
        temp.id = i;
        temp.arrival_time = at;
        temp.execution_time = et;
        enqueue(request_arr, temp, &back);
    }

    // Sorting requests by arrival time
    bubble_sort(request_arr, n);


    // Running simulation
    int final_id = request_arr[n - 1].id;
    int time = 0;
    while (peek(request_arr, front).id != final_id) {
        struct request candidate_request = peek(request_arr, front);
        if (candidate_request.arrival_time <= time) {
            time += candidate_request.execution_time;
            dequeue(request_arr, &front);
            printf("P%d -> ", candidate_request.id);
        } else {
            // Waiting code here
            time += 1;
        }
    }

    // Appending final request manually
    time += peek(request_arr, front).execution_time;
    printf("P%d -> ", peek(request_arr, front).id);
    printf("END\n-----------\nTotal CPU time: %d", time);

}