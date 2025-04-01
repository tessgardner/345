#ifndef SIGNALTOOLS_H
#define SIGNALTOOLS_H

// sets up specific signals, when a signal is sent a function
// will run instead of normal signal fucntion
// - signal is the signal type (i.e., SIGTERM)
// - 2nd argument (*handler) is the function reference that a signal will use
// when that signal is sent to the process
void setUpSignal(int signal, void (*handler)(int));

// used to block/unblock signals from interacting with the process
// - signal is the signal type (i.e., SIGTERM)
// - showMessage shows the blocked or unblocked message, useful for debugging
void blockSignal(int signal, int showMessage);
void unblockSignal(int signal, int showMessage);

// shows some information about a signal
// - signal is the signal type (i.e., SIGTERM)
void printSignalInfo(int signal);

// run test cases for the following signals:
// - SIGINT
// - SIGUSR1
void runTestCases();

#endif