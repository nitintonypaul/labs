#include <stdio.h>

struct request {
    int id;
    int arrival_time;
    int burst_time;
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

int maxburst(struct request *arr, int length) {
    int max = 0;
    for (int i = 0; i < length; i++) {
        if (arr[i].burst_time > max) max = arr[i].burst_time;
    }
    return max;
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

int main() {

    // Obtaining number of requests
    int n;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    // Obtaining time quanta
    int q;
    printf("Enter time quanta: ");
    scanf("%d", &q);
    
    // Request array
    struct request request_arr[n];

    // Obtaining requests
    for (int i = 0; i < n; i++) {
        int at, et;
        printf("Enter arrival time of P%d: ", i);
        scanf("%d", &at);
        printf("Enter burst time of P%d: ", i);
        scanf("%d", &et);

        struct request temp;
        temp.id = i;
        temp.arrival_time = at;
        temp.burst_time = et;
        request_arr[i] = temp;
    }

    // Sorting with arrival time
    bubble_sort(request_arr, n);

    // Enqueueing all requests within array
    int maximum_burst = maxburst(request_arr, n);
    struct request Q[
        (n+1) * ((maximum_burst + q - 1) / q)
    ];
    int FRONT = 0;
    int BACK = 0;
    for (int i = 0; i < n; i++) {
        enqueue(Q, request_arr[i], &BACK);
    }

    // Running simulation
    int time = 0;
    while (FRONT < BACK) {
        // Check if process has arrived
        if (peek(Q, FRONT).arrival_time <= time) {
            // Pull out process
            struct request temp = dequeue(Q, &FRONT);

            // run process for q time if remaining burst is > q
            if (temp.burst_time <= q) {
                time += temp.burst_time;
                printf("P%d -> ", temp.id);
                continue;
            } else {
                temp.burst_time -= q;
                time += q;
                printf("P%d -> ", temp.id);

                // Push it back into queue if not completed
                enqueue(Q, temp, &BACK);
            }
        } else {
            time += 1;
        }
    }
    printf("END\n-----------\nTotal CPU time: %d", time);
}