#include <stdio.h>

typedef struct something_st SOMETHING;

typedef int integer;

struct tag {
};
typedef struct tag T;

typedef struct tag2 {
} T2;

typedef struct name {
  char* name;
  unsigned int flag1:1;
  unsigned int flag2:2;
} something;

int main(int argc, char** argv) {
  something s = {"bajja", 1, 1};
  printf("%s.name, s.flag1: %d, s.flag2: %d\n", s.name, s.flag1, s.flag2);
  s.flag1++;
  s.flag2++;
  // Notice that only 1 bit is used for this to incrementing will become 0
  printf("%s.name, s.flag1: %d, s.flag2: %d\n", s.name, s.flag1, s.flag2);

  struct tag t;
  T t2;
  T2 tt2;

  integer i = 18;
  printf("integer=%d\n", i);

  SOMETHING* st = NULL;

  return 0;
}
