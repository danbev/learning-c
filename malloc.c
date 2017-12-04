#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int* ptr = malloc(1 * sizeof(int));
  *ptr = 22;
  printf("&p=%p value=%d\n", &ptr, *ptr);
  // frees the space but that does not mean that it is cleared (replaced 
  // by something else. 
  // Also not that free gets a copy of ptr so ptr will still point to the
  // old memory location
  free(ptr);
  printf("After free &p=%p value=%d\n", &ptr, *ptr);
  return 0;
}
