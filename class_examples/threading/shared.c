#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // THREAD LIBRARY

int sum = 0; // shared by all threads

// PUT AN INTEGER INTO COMMAND LINE WHEN RUNNING THIS

void *partialSum (void *param) {
    int upper = atoi((char *)param);
    for (int i = 1; i <= upper; i++) {
        sum += i;
    }
    printf("Thread id = %lu done\n", pthread_self());
    pthread_exit(0);
}

int main (int argc, char *argv[]) {

    if (argc != 2) { // Ensure user provides an argument
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }
    pthread_t tid1; // thread ID!
    pthread_t tid2; // thread ID!

    pthread_attr_t attr; // set of attributes
    pthread_attr_init(&attr);

    pthread_create(&tid1, &attr, partialSum, argv[1]);
    pthread_create(&tid2, &attr, partialSum, argv[1]);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Sum = %d\n", sum);
    return 0;
}