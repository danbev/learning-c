#include <stdio.h>
#include <stdlib.h>

void something() __attribute__((noreturn));

void myExit() {
  exit(1);
}

void something()  {
  printf("something...\n");
  // this does infact return as it does not exit or 
  // enter an infinit loop or anything.
  myExit();
}

int main() {
  printf("no-return...\n");
  something();
  return 0;
}
