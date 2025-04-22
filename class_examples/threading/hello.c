#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // THREAD LIBRARY
// thread calls this!!

void *sayHello (void *varargs){
    printf("Hello, world!\n");
    pthread_exit(0);
} 

int main() {
    pthread_t tid; // THREAD ID
    pthread_create(&tid, NULL, sayHello, NULL);
    pthread_join (tid, NULL);
    return 0;
}

