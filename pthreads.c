#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void *func(void *args);

pthread_once_t init_mutex = PTHREAD_ONCE_INIT;

/*
 * This will only be called once for regardless of how many thread call it.
 */
void init_thread(void) {
    printf("initializing new thread....\n");
}

int main() {
    int number = 10;
    printf("bacic...\n");
    pthread_t t;
    // creating a thread with NULL attributes is the same thing as creating on with default
    // attributes. Would be the same as calling pthread_attr_init()
    // The attributes specifies various characteristics for the new thread.
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    for (int i = 0; i < 10; i++) {
        //
        int ret = pthread_create(&t, &attr, func, &number);
        if (ret != 0) {
            printf("Could not start pthread (%s)", strerror(errno));
            exit(-1);
        }
    }
    pthread_exit(NULL);
    return 0;
}

void * func(void *args) {
    // for example the first thread might have to perform stuff but this 
    // stuff should only be done once.
    pthread_once(&init_mutex, &init_thread);
    int *nr = (int *) args;
    printf("in func...%d\n", *nr);
    pthread_t pt = pthread_self();
    printf("Thread nr:.%x\n", (int) pt);
    return NULL;
}
