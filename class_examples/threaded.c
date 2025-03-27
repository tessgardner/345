#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h> // THREAD LIBRARY

#define NUM_THREADS 4;
#define TASK_SIZE 100000000

void *perform_work (void *arg) {
    int index = *((int *) arg);
    long sum = 0;
    for (int i = 0; i < TASK_SIZE; i ++) {
        sum += i;
    }
    printf("Thread %d, Sum = %ld\n", index, sum);

    free(arg); // freeing up memory!
    pthread_exit(0); // or return NULL;
}

int main () {
    pthread_t threads[NUM_THREADS]; // holds all IDs for threads (4 in this case!)
    int rc; // returns code for showing errors
    struct timespec start, finish; 
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);

    // creating threads
    for (int i = 0; i < NUM_THREADS; i++) {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        rc = pthread_create(&thread[i], NULL, perform_work, (void*) arg);
        if (rc) {
            printf("ERROR; return code from pthread_create is %d\n", rc);
            exit(-1);
        }
    }

    // setting up ready state for threads
    for (int i = 0; i < NUM_THREADS; i++) {
       pthread_join(thread[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finished.tv_sec - start.tv_sec);
    elapsed += (finished.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Threaded executon: %.5f seconds\n", elapsed);

    return 0;
}