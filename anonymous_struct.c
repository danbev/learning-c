#include <stdio.h>

struct something {
  union {
    char c;
    int x;
  } uni;
};

int main(int argc, char** argv) {
  struct something s;
  s.uni.c = 'A';
  printf("s.uni.c: %c\n", s.uni.c);
  printf("Set s.uni.x = 2\n");
  s.uni.x = 2;
  printf("Notice that s.uni.c was overwritten:\n");
  printf("s.uni.c: %d, &s.uni.c: %p \n", s.uni.c, &s.uni.c);
  printf("s.uni.x: %d, &s.uni.x: %p \n", s.uni.x, &s.uni.x);

}
