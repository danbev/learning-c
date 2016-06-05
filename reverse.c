#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  if (argc != 2) {
    printf("Usage: %s filename\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if ((fp = fopen(argv[1], "r")) == NULL) {
    printf("Error while trying to open: %s filename\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  fseek(fp, 0L, SEEK_END);
  long last = ftell(fp);
  char ch;
  for (long i = 1L; i <= last; i++) {
    fseek(fp, -i, SEEK_END);
    ch = getc(fp);
    printf("%c", ch);
  }
  fclose(fp);
  return 0;
}
