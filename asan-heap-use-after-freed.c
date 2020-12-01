#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// $ gcc -g3 -o asan -fsanitize=address asan.cc 
int main(int argc, char** argv) {
  int* ptr = malloc(sizeof(int));
  *ptr = 2;
  printf("*ptr (%p): %d\n", ptr, *ptr);

  int* ptr2 = ptr;

  free(ptr);
  // The next file will genereate a heap-use-after-free error by asan
  printf("*ptr2 (%p): %d\n", ptr2, *ptr2);

  return 0;
}
