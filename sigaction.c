#include <signal.h> // in /usr/include/sys/signal.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void handler(int signo) {
    if (signo == SIGUSR1) {
        printf("SIGURS1. Just printing. Carry on\n");
    } else if (signo == SIGUSR2) {
        printf("SIGUP. Going to exit\n");
        exit(EXIT_SUCCESS);
    }
}

// kill -USR1 16932
//
int main(int argc, char **argv) {
    printf("pid: %d\n", getpid());
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    for (;;) {
    }
    return 0;
}
