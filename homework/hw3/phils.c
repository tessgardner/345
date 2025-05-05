#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

int numOfPhils; // number of phils, passed in as argument[1]
int numOfTimesToEat; // number of times to eat each, passed in as argument[2]
sem_t *forks; // points to an array of semaphores (forks)
int *state; // thinking, hungry, or eating. points to an array of integers, each one represents stae of the philosopher
int *phils; // &phils[i] is thread ID/thread index

// THINKING = 0
// HUNGRY = 1
// EATING = 2

void pickupFork(int index) {  // HUNGRY STATE
    // waits to grab forks for philospher
    state[index] = 1; // setting state of current philospher to hungry
    
    printf("Philosopher %d is hungry...\n", phils[index]); // displaying that philosopher is hungry
 
    if (index % 2 == 0) { // if the philospher is even...
        sem_wait(&forks[index]); // pick up left fork (also decrementing semaphore)
        sem_wait(&forks[(index + 1) % numOfPhils]); // pick up right fork (also decrementing semaphore)
    } else { // if the philosopher is odd....
        sem_wait(&forks[(index + 1) % numOfPhils]); // pick up right fork (also decrementing semaphore)
        sem_wait(&forks[index]); // pick up left fork (also decrementing semaphore)
   }
    state[index] = 2; // setting state of current philospher to hungry 
    printf("Philosopher %d is eating...\n", phils[index]); // displaying that philosopher is eating
}

void putDownFork(int index) { // THINKING STATE
    // puts forks back down 
    // can't pick up fork in this state

    state[index] = 0; // setting state of current philosopher to thinking

    sem_post(&forks[index]); // putting down left fork (also incrementing semaphore)
    sem_post(&forks[(index + 1) % numOfPhils]); // putting down right fork (also incrementing semaphore)

    printf("Philosopher %d is thinking...\n", phils[index]); // displaying that philosopher is thinking
}

void *philosopher(void * threads) { // recieves each thread

    int index = *((int *) threads); // identifies index of current thread
    
    // determines first action of a philospher when thread is created (hungry or thinking only)
    int rd_num = rand() % 2; // randomizer chooses 1 (hungry) or 0 (thinking)
    state[index] = rd_num; // index is set to what the randmizer chose

    // this loop executes the number of times each philospher needs to eat food 
    for (int i = 0; i < numOfTimesToEat; i ++) {
        sleep(0.5);
        pickupFork(index);
        sleep(0.5);
        putDownFork(index);
    }
    pthread_exit(0);
} 

int main(int argc, char *argv[]) {
    
    // initializing command line arguments
    numOfPhils = atoi(argv[1]);
    numOfTimesToEat = atoi(argv[2]);
    
    pthread_t threads[numOfPhils]; // holds all IDs for threads/philosophers
  
    // memory allocation for forks, state, and philosphers
    forks = malloc(numOfPhils * sizeof(sem_t));
    state = malloc(numOfPhils * sizeof(int));
    phils = malloc(numOfPhils * sizeof(int));

    // creating and joining the threads
    // also gives each thread an initial state of hungry or thinking
    for (int i = 0; i < numOfPhils; i ++) { // loops for number of threads
        phils[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &phils[i]);
        sem_init(&forks[i], 0, 1); // binary semaphore initialized
        // 1 = avaliable
        // 0 = unavaliable
    }

    // waiting for threads to finish and synchronize
    for (int i = 0; i < numOfPhils; i++) {
        pthread_join(threads[i], NULL);
    }

    // freeing up memory at the end
    free(forks);
    free(state);
    free(phils);
    return 0;
}
