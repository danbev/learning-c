#include <stdio.h>

void one() {
  printf("one\n");
}

void two() {
  printf("two\n");
}

void three(char* s) {
  printf("%s\n", s);
}

#define DOIT(s) \
  (one(), two(), three)(s)


int main(int argc, char** argv) {
  one(), two(), three("3");
  DOIT("3");
  return 0;
}
