#include <stdio.h>
__attribute__ ((__constructor__)) void pre_func(void) {
  printf("init...\n");
}
