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
    if (signal(SIGUSR1, handleSignal) == SIG_ERR) {
      fprintf(stderr, "Cannot handle SIGUSR1 \n");
      exit(EXIT_FAILURE);
    }
    if (signal(SIGUSR2, handleSignal) == SIG_ERR) {
      fprintf(stderr, "Cannot handle SIGUSR2 \n");
      exit(EXIT_FAILURE);
    }
    for (;;) {
      pause();
    }
    return 0;
}
