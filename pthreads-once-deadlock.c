#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void *func(void *args);

pthread_once_t init_mutex = PTHREAD_ONCE_INIT;

void something(void) {
  printf("something.....\n");
}
/*
 * This will only be called once for regardless of how many thread call it.
 */
void once(void) {
  printf("Once.....\n");
  int p = pthread_once(&init_mutex, &something);
  printf("pthread_once from callback returned: %d\n", p);
}


int main() {
    int number = 10;
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

void* func(void *args) {
    // for example the first thread might have to perform stuff but this 
    // stuff should only be done once.
    int p = pthread_once(&init_mutex, &once);
    printf("pthread_once returned: %d\n", p);
    return NULL;
}
