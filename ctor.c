#include <stdio.h>

/* This example is just used for trying out __attribute__((constructor))
 * which is defined in ctor2.cc
 */
int main() {
  printf("main...\n");
  return 0;
}
