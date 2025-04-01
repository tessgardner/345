// Name: Tess Gardner
// Date: 03/25/25
// Description: C program that responds to specific signals SIGINT, 
// SIGTERM, SIGUSR1, and SIGUSR2 by using signal handlers and blocking 
// signals, and runs as an infinite loop that can handle signals dynamically.

// libraries neeeded
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include "signalTools.h" 

// variable to keep track of signal blocking status
// 1 = blocked, 0 = unblocked
int isBlocked = 1; 

// documents time of start of program
time_t seconds_start;

// FUNCTIONS:

// toggles the SIGUSR1 signal
void handle_SIGINT(int signal) {

    // prints what signal was received
    printSignalInfo(signal);

    // if the signal is blocked, unblock it and update status
    if (isBlocked == 1) {
        unblockSignal(SIGUSR1, 1);
        isBlocked = 0;
        printf("SIGINT received: Unblocking SIGUSR1\n");  
    // if the signal is unblocked, block it and update status
    } else {
        blockSignal(SIGUSR1, 1);
        printf("SIGINT received: Blocking SIGUSR1\n"); 
        isBlocked = 1; 
    }
}

// exits the program
void handle_SIGTERM(int signal) { 

    // prints what signal was received
    printSignalInfo(signal);

    printf("SIGTERM received: Exiting the program.\n"); 

    // software termination signal
    exit(0);
}

// must be toggled by SIGINT
// displays current system info and saves it to status.txt
void handle_SIGUSR1(int signal) { 

    // prints what signal was received
    printSignalInfo(signal);

    // blocking signal
    if (isBlocked == 1) {
        return;
    }

    // calculate uptime and current time
    time_t seconds_current = time(NULL);
    time_t uptime = seconds_current - seconds_start;
    time_t current_time;
    time(&current_time);

    // searching for or initializing status.txt
    FILE *statptr = fopen("status.txt", "a");

    // ensuring the file can be opened/initialized
    if (statptr == NULL) {
        printf("Error opening source file.\n");
        return;
    }

    // printing output 
    printf("### Status Report ###\n");
    printf("Current time: %s\n", ctime(&current_time));
    printf("Uptime: %ld seconds\n", uptime);
    printf("### End of Report ###\n");

    //  putting ouput into status.txt
    fprintf(statptr, "### Status Report ###\n");
    fprintf(statptr, "Current time: %s\n", ctime(&current_time));
    fprintf(statptr, "Uptime: %ld seconds\n", uptime);
    fprintf(statptr, "### End of Report ###\n");

    // closing status.txt
    fclose(statptr);
}

// should print a log of current system information then save it to 
// status.txt
void handle_SIGUSR2(int signal) { 
    // prints what signal was received
    printSignalInfo(signal);

    //  runs the test cases provided by runTestCases
    runTestCases();
}

int main() {

   // displaying process ID
   printf("Program started. PID: %d\n", getpid());

   // setting up the 4 signals
   setUpSignal(SIGUSR1, handle_SIGUSR1);
   setUpSignal(SIGUSR2, handle_SIGUSR2);
   setUpSignal(SIGINT, handle_SIGINT);
   setUpSignal(SIGTERM, handle_SIGTERM);

   printf("Waiting for signals ...\n");

    // infinite loop so that the program is inifintely waiting 
    // for a signal
    for (;;) {
        pause();
    }
    return 0;
}