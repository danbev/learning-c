#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

void * signal_waiter(void *times) {
    printf("in signal_waiter\n");
    int caught;
    sigset_t signals_to_catch;
    sigemptyset(&signals_to_catch);
    sigaddset(&signals_to_catch, SIGUSR1);
    for (;;) {
        // will block until the signals arrives
        // $ kill -USR1 18407
        sigwait(&signals_to_catch, &caught);
        printf("got signal\n");
        break;
    }
    return NULL;
}

int main(int argc, char** argv) {
    printf("pthread sigwait pid=%d.\n", getpid());
    sigset_t signals_to_block;

    // empty the signal set
    sigemptyset(&signals_to_block);
    // add the signal to block
    sigaddset(&signals_to_block, SIGUSR1);
    pthread_sigmask(SIG_BLOCK, &signals_to_block, NULL);

    pthread_t t1;
    if(pthread_create(&t1, NULL, signal_waiter, NULL)) {
        printf("Could not create pthread\n");
        exit(1);
    }
    if(pthread_join(t1, NULL)) {
        printf("Could not join pthread\n");
        exit(1);
    }
    return 0;
}
