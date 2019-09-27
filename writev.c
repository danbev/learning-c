#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/uio.h>

int main(int argc, char** argv) {
  const char buf1[] = "Something...";
  const char buf2[] = "Something... ";
  const char buf3[] = "Bajja!\n";

  struct iovec bufs[] = {
    { .iov_base = (void *) buf1, .iov_len = sizeof(buf1) },
    { .iov_base = (void *) buf2, .iov_len = sizeof(buf2) },
    { .iov_base = (void *) buf3, .iov_len = sizeof(buf3) },
  };

  if (writev(STDOUT_FILENO, bufs, 3) == -1) {
    perror("writev()");
    exit(EXIT_FAILURE);
  }

  return 0;
}
