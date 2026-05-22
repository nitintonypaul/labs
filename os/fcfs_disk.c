#include <stdio.h>

int main() {
    int n;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n];
    for (int i  = 0; i < n; i++) {
        printf("Enter request %d: ", i+1);
        scanf("%d", &req[i]);
    }

    int head;
    printf("Enter head position: ");
    scanf("%d", &head);

    int totalmovement = 0;
    printf("%d -> ", head);
    for (int i = 0; i < n; i++) {
        printf("%d -> ", req[i]);
        int candidate = req[i] - head;
        if (candidate < 0) {
            candidate *= -1;
        }
        totalmovement += candidate;
        head = req[i];
    }
    printf("END\n----------\n");
    printf("Total head movement: %d", totalmovement);

    return 0;

}