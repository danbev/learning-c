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

int main(int argc, char **argv) {
    printf("pid: %d\n", getpid());
    void (*old)(int);
    old = signal(SIGUSR1, handleSignal);
    signal(SIGUSR2, handleSignal);
    for (;;) {
    }
    return 0;
}
