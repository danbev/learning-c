#include <signal.h> // in /usr/include/sys/signal.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



void handleSignal(int signo) {
    if (signo == SIGUSR1) {
        printf("SIGURS1. Just printing. Carry on\n");
    } else if (signo == SIGUSR2) {
        printf("SIGUP. Going to exit\n");
        exit(EXIT_SUCCESS);
    }
}

// kill -USR1 16932
//
// void (*signal(int sig, void (*func)(int)))(int);
// So what we have is a function pointer, signal which takes an int
// and a function pointer of that takes an int and returns nothing.
// The signal function itself returns an a function pointer to the
// previous handler (if any). And a handler returns void and takes an
// int which explains the first void and the last (int)
//
int main(int argc, char **argv) {
    printf("pid: %d\n", getpid());
    void (*old)(int);
    old = signal(SIGUSR1, handleSignal);
    signal(SIGUSR2, handleSignal);
    for (;;) {
    }
    return 0;
}
