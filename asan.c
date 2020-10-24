#include <stdio.h>
#include <string.h>

// $ gcc -g3 -o asan -fsanitize=address asan.cc 
int main(int argc, char** argv) {
  char line[] = "Something something";
  char mem[18];

  strcpy(mem, line);

  printf("mem: %s\n", mem);

  return 0;
}
