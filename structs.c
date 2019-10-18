#include <stdio.h>

typedef int integer;

struct tag {
};
typedef struct tag T;

typedef struct tag2 {
} T2;

typedef struct name {
  char* name;
} something;

int main(int argc, char** argv) {
  something s = {"bajja"};
  printf("%s\n", s.name);

  struct tag t;
  T t2;
  T2 tt2;

  integer i = 18;
  printf("integer=%d\n", i);

  return 0;
}
