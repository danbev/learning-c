#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

int counter = 0;
sem_t *sem;

void * increment(void *times) {
    // try lock the semaphore which will succeed if the 1, which will decrement the value to 0.
    int r = sem_wait(sem);
    int *t = (int*) times;
    for (int i = 0; i < *t; i++) {
        int c = counter;
        c++;
        counter = c;
    }
    // unlock the semaphore and increment the value to 1
    sem_post(sem);
    return NULL;
}

int main(int argc, char** argv) {
    // use a named semaphore which is a semphore which can an unrelated process can 
    // access by name:
    sem = sem_open("/counter", O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
        printf("Failed to create semaphore\n");
        exit(1);
    }

    int times = 1000;
    printf("pthread semaphore example.\n");
    pthread_t t1, t2;
    if(pthread_create(&t1, NULL, increment, &times)) {
        printf("Could not create pthread\n");
        exit(1);
    }
    if(pthread_create(&t2, NULL, increment, &times)) {
        printf("Could not create pthread\n");
        exit(1);
    }
    if(pthread_join(t1, NULL)) {
        printf("Could not join pthread\n");
        exit(1);
    }
    if(pthread_join(t2, NULL)) {
        printf("Could not join pthread\n");
        exit(1);
    }
    if (counter == 2000) {
        printf("counter = %d so all good.\n", counter);
    } else {
        printf("Not good, counter = %d\n", counter);
    }

    return 0;
}
