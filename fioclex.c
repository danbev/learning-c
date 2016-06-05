#include <stdio.h>
#include <stdlib.h> // exit
#include <sys/ioctl.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
 * An example of using ioctl and File IOCtl on Exec (FIOCEX)
 *
 * Bascially we want to ensure that any file descriptors that are opened 
 * before the call to exec are closed. exec initiates a program from within
 * another program. Recall that exec replaces the current process image 
 * with a new process image
 *
 */
int main(int argc, char *argv[]) {
    int ch;
    FILE *fp;
    unsigned long count = 0;
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("Can't open: %s filename\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    int r = ioctl(fileno(fp), FIOCLEX);
    printf("File IOCtl CLose on EXec returned %d\n", r);
    execl("/bin/ls", "/bin/ls", "-r", "-t", "-l", (char *) 0);
    // nothing after this point in the program will execute as the current processes
    // image will have been replaced.
    return 0;
}
