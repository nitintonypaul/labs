#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int *numbers;
int count;
float mean = 0.0;
float median = 0.0;
float std = 0.0;

void *find_mean(void *arg) {
    float sum = 0.0;
    for (int i = 0; i < count; i++) sum += numbers[i];
    mean = sum / count;

    pthread_exit(NULL);
}

void *find_median(void *arg) {
    if (count % 2 == 0) {
        median = (numbers[count/2 - 1] + numbers[count/2]) / 2.0;
    } else {
        median = numbers[count / 2];
    }

    pthread_exit(NULL);
}

void *find_std(void *arg) {
    float squared_sum = 0.0;
    for (int i = 0; i < count; i++) squared_sum += pow(numbers[i] - mean, 2);
    std = sqrt(squared_sum / count);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    count = argc - 1;
    numbers = malloc(count * sizeof(int));
    for (int i = 1; i < count; i++) {
        numbers[i-1] = atoi(argv[i]);
    }

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, find_mean, NULL);
    pthread_create(&t2, NULL, find_median, NULL);
    pthread_join(t1, NULL);
    pthread_create(&t3, NULL, find_std, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // Results or whatever

    return 0;
}