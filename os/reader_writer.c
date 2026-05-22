#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

sem_t rw_mutex;
sem_t rmutex;
sem_t readtry;
sem_t wmutex;
int read_count = 0;
int write_count = 0;


void *reader(void *arg) {
    int id = *(int *)arg;

    sem_wait(&read_try);
    sem_wait(&rmutex);
    read_count++;
    if (read_count == 1) sem_wait(&rw_mutex);
    sem_post(&rmutex);
    sem_post(&read_try);

    // Critical Section
    printf("Reader %d is READING\n", id);
    sleep(1);
    printf("Reader %d is DONE reading\n", id);

    sem_wait(&read_try);
    sem_wait(&rmutex);
    read_count--;
    if (read_count == 0) sem_post(&rw_mutex);
    sem_post(&rmutex);
    sem_post(&read_try);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

    sem_wait(&wmutex);
    write_count++;
    if (write_count == 1) sem_wait(&read_try);
    sem_post(&wmutex);

    sem_wait(&rw_mutex);

    // Critical Section
    printf("\tWriter %d is WRITING\n", id);
    sleep(2);
    printf("\tWriter %d is DONE writing\n", id);

    sem_post(&rw_mutex);
    sem_wait(&wmutex);
    write_count--;
    if (write_count == 0) sem_post(&read_try);
    sem_post(&wmutex);

    return NULL;
}
int main() {
    pid_t r[5], w[5];
    int ids[5];

    for (int i = 0; i < 5; i++) {
        ids[i] = i+1;
    }

    for (int i = 0; i < 5; i++) {
        pthread_create(&r[i], NULL, reader, &ids[i]);
        pthread_create(&w[i], NULL, reader, &ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(r[i], NULL);
        pthread_join(w[i], NULL);
    }

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}