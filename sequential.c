#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h> // THREAD LIBRARY

// CONSTANT
#define TASK_SIZE 100000000;

long perform_work() {
    long sum = 0;
    for (long i = 0; i < TASK_SIZE; i++) {
        sum += i;
        return sum;
    }
}

int main() {
    struct timespec start, finish;
    double elapsed;
    clocked_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < 4; i++) {
        long sum = perform_work();
        printf("Iteration %d, Sum = %ld\n", i, sum);
    }
    clock_gettime(CKICK_MONOTONIC, &finish);

    elapsed = (finished.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 100000000.0;
    printf("Sequentoal execution: %.5f seconds\n", elapsed);

    return 0;
}