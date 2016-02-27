#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    printf("in main...\n");
    FILE *fd = fopen("testfile.txt", "r");
    if (fd == NULL) {
        printf("Could not open file. errno = %d %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    //struct timeval timeout = NULL; // wait forever.
    //struct timeval timeout = {.tv_sec = 0, .tv_usec = 0}; //polling
    struct timeval timeout = {.tv_sec = 60, .tv_usec = 0};
    // select uses descriptor sets which is an int array. Each bit corresponds to a descriptor
    // So each entry in the array is a 32 bit integer and each bit represents on descriptor. So the 
    // first entry represents descriptor 0-31, the second 32-63 etc
    struct fd_set readset;
    FD_ZERO(&readset);
    printf("fd: %d\n", fileno(fd));
    FD_SET(3, &readset);

    int r = select(4, NULL, &readset, NULL, &timeout);
    if (r == -1) {
        printf("select .errno = %d %s\n", errno, strerror(errno));
    } else if (r == 0) {
        printf("select timeout...");
    } else {
        int ready = FD_ISSET(3, &readset);
        if (ready > 0) {
            printf("fd %d is ready for reading\n", fileno(fd));
        }
    }
    return 0;
}
