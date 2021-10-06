#include <stdio.h>

void f(int n, int[n]);
void f(int, int[]);     // warning: argument 2 previously declared as a VLA

void g(int n) {
  int a[n];
  for (int i = 0; i < n; i++) {
    a[i] = i;
    printf("a[%d]: %d\n", a[i], i);
  }
  f (sizeof a, a);     // warning: access to a by f may be out of bounds
}

void f(int n, int[n]) {
}

int main(int argc, char** argv) {
  printf("-Wvla-parameter (Variable-Length-Array) example\n");
  g(10);
  return 0;
}

