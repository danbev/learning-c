#include <sys/poll.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) {
    printf("poll() example\n");
    struct pollfd fds = {0, POLLIN, 0};

    int timeout = 5000;
    int err;

    int nr_fds = 1; // number of entries in polldf struct
    err = poll(&fds, nr_fds, timeout);
    if (err == 0) {
      printf("poll() timed out\n");
    } else if (err == -1) {
      printf("poll() failed out: %s\n", strerror(errno));
    } else {
      printf("poll() data available!\n");
      if (fds.revents & POLLIN) {
        char buf[32];
        ssize_t n = read(0, &buf, 32); 
        printf("read: (%d bytes): %s", n, buf);
      }
    }

    return 0;
}
