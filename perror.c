#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv) {
  for (size_t i = 0; i < sys_nerr; i++) {
    printf("%*zu = %s\n", 3, i, strerror(i));
  }

  errno = 1;
  perror("Error, something happened");

  return 1;
}
