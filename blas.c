#include <cblas.h>
#include <stdio.h>

int main(int argc, char** argv) {
  printf("BLAS example\n");
  double x[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double y[] = {5.0, 4.0, 3.0, 2.0, 1.0};
  int n = 5;

  // add the two vectors
  cblas_daxpy(n, 1.0, x, 1, y, 1);
  printf("Result of vector addition: ");
  for(int i = 0; i < n; i++) {
    printf("%.1f ", y[i]);
  }
  printf("\n");
}
