#include <sys/event.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char TEST_FILE[] = "./test.txt";

int main(void) {
    // the kqueue file descriptor returned from creating a kernal queue.
    int kq;
    // file descriptor for the file we are monitoring
    int fd;
    // new events that are returned from kevent
    int nev;
    // the new events that we want to the kernel to notifiy us about.
    struct kevent change;
    // the events that kevent is reporting. This gets filled by the kernel
    struct kevent event;

    kq = kqueue();
    if (kq == -1) {
        perror("kqueue");
    }

    printf("Test file: %s\n", TEST_FILE);
    fd = open(TEST_FILE, O_RDONLY);
    if (fd == -1) {
        perror("open");
    }
    EV_SET(&change, fd, EVFILT_VNODE,  EV_ADD | EV_ENABLE | EV_CLEAR, NOTE_WRITE | NOTE_DELETE, 0, (void *) TEST_FILE);

    for (;;) {
        nev = kevent(kq, &change, 1, &event, 1, NULL); //NULL is the timeout struct.
        if (nev == -1) {
            perror("kevent");
        } else if (nev > 0) {
            if (event.fflags & NOTE_DELETE) {
                printf("File deleted. Exiting\n");
                break;
            }
            if (event.fflags & NOTE_WRITE) {
                char * data = (char *) event.udata;
                printf("File[%s] modified\n", data);
            }
            if (event.fflags & NOTE_ATTRIB)  {
            printf("File attributes modified\n");
          }
        }
    }
    close(kq);
    close(fd);
    return EXIT_SUCCESS;
}
