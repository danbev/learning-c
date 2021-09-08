#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) {
    printf("select() example\n");
    fd_set rd;
    fd_set* wr = NULL;
    fd_set* ex = NULL;

    struct timeval timeout;
    int err;

    FD_ZERO(&rd); // create and set to zero
    FD_SET(0, &rd); // set file descriptor we are interested, 0=stdin

    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    int nr_fds = 1;
    err = select(nr_fds, &rd, wr, ex, &timeout);
    if (err == 0) {
      printf("select() timed out\n");
    } else if (err == -1) {
      printf("select() failed out: %s\n", strerror(errno));
    } else {
      printf("select() data available!\n");
      char buf[32];
      ssize_t n = read(0, &buf, 32); 
      printf("read: (%d bytes): %s", n, buf);
    }

    return 0;
}
