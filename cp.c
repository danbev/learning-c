#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *src, *dst;
  if (argc < 3) {
    fprintf(stderr, "Usage: %s source destination\n", argv[0]); 
    exit(EXIT_FAILURE);
  }

  if ((src = fopen(argv[1], "r")) == NULL) {
    printf("Could not open source :%s \n", argv[1]); 
    exit(EXIT_FAILURE);
  }
  if ((dst = fopen(argv[2], "w")) == NULL) {
    printf("Could not open destination :%s \n", argv[2]); 
    exit(EXIT_FAILURE);
  }
  int ch;

  while ((ch = getc(src)) != EOF) {
    printf("%c", ch);
    fprintf(dst, "%c", ch);
  }
  if (fclose(src) != 0) {
    printf("Could not close source :%s \n", argv[1]); 
    exit(EXIT_FAILURE);
  }
  if (fclose(dst) != 0) {
    printf("Could not close destination :%s \n", argv[2]); 
    exit(EXIT_FAILURE);
  }
  printf("Copies %s to %s\n", argv[1], argv[2]);
  return 0;
}
