#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

// can be found in /usr/include/pthread.h
pthread_mutex_t number_mutex = PTHREAD_MUTEX_INITIALIZER;

void *func(void *args);

int main() {
    int number = 4;
    int *nptr = &number;
    printf("pthread mutexes\n");
    pthread_t t1;
    pthread_t t2;
    pthread_create(&t1, NULL, func, &nptr);
    // kind of synchronization where we let t1 perform its works first
    pthread_join(t1, NULL);
    pthread_create(&t2, NULL, func, &nptr);
    pthread_join(t2, NULL);

    // without a mutext these two threads would not print number in
    // incremental order. Not a great example but.
    pthread_create(&t1, NULL, func, &nptr);
    pthread_create(&t2, NULL, func, &nptr);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

void * func(void *args) {
    int **nr = (int **) args;
    pthread_mutex_lock(&number_mutex);
    printf("in func...%d\n", **nr);
    // lock blocks. You could use tryLock if you cannot block
    **nr = **nr + 1;
    pthread_mutex_unlock(&number_mutex);
    pthread_t pt = pthread_self();
    printf("Thread nr:.%x\n", (int) pt);
    pthread_exit(NULL);
    return NULL;
}
