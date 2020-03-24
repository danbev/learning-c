#include <stdio.h>
#include "something.h"
#include "sharedsomething.h"

int main(int argc, char** argv) {
  printf("cmake example...\n");
  something();
  shared_something();
  return 0;
}
