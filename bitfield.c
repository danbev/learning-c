#include <stdio.h>

struct something_non {
  unsigned p_1;
  unsigned p_2;
};

struct something {
  unsigned p_1 : 1;
  unsigned p_2 : 1;
};

int main(int argc, char** argv) {
  struct something_non s_none = {1, 0};
  struct something s = {1, 0};
  printf("sizeof(s_non}): %d\n", sizeof(s_none));
  printf("sizeof(s}): %d\n", sizeof(s));
  return 0;
}
