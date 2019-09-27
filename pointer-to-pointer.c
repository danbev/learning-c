#include <stdio.h>

int main(int argc, char** argv) {
  char const* s = "bajja";
  char const** ss;
  ss = &s;

  printf("size of char=%lu\n", sizeof(char*));
  printf("argv=%p\n", argv);
  return 0;
}
