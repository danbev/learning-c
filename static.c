#include <stdlib.h>
#include <stdio.h>

void something(int nr[static 2]) {
  printf("something %d\n", nr[0]); 
  printf("something %d\n", nr[1]); 
} 

int main(int argc, char** argv) {
  something(NULL);
  int y[1];
  something(y);
  return EXIT_SUCCESS;
}
