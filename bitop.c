#include <stdio.h>

void bin(unsigned n) {
  unsigned i;
  for (i = 1 << 31; i > 0; i = i / 2)
    (n & i) ? printf("1") : printf("0");
  printf("\n");
}

int main(int argc, char** argv) {
  printf("bit operation examples\n");
  int ref = 0x00000008;
  int active = 0x00000004;
  unsigned int flags = ref;

  printf("init state: %d\n", flags);

  printf("flags & ref: %d\n", flags & ref);

  printf("ref:\n");
  bin(ref);
  printf("~ref:\n");
  bin(~ref);

  flags &= ~ref;
  printf("flags &= ~ref:\n");
  bin(flags);

  printf("flags & active: %d\n", flags & active);
  bin(active);

  flags |= active;
  printf("flags |= : %d\n", flags);
  bin(flags);

  return 0;
}
