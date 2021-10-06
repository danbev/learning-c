#include <stdio.h>

void f(int n, int[n]);

void g(int n) {
  int a[n];
  for (int i = 0; i < n; i++) {
    a[i] = i;
    printf("a[%d]: %d\n", a[i], i);
  }
}

//void f(int n, int[n]) { // having the same signature will suppress this warning
void f(int n, int[]) {  // warning: argument 2 previously declared as a VLA
}

int main(int argc, char** argv) {
  printf("-Wvla-parameter (Variable-Length-Array) example\n");
  g(10);
  return 0;
}

