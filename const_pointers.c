#include <stdio.h>

int one = 1;
int two = 2;

void fun1(int* p) {
  p = &two;
}

void fun(int** p) {
  **p = 2;
}

int main(void) {
  int nr = 10;
  int* p = &nr;
  int** pp = &p;
  printf("&nr=%p\n", &nr);
  printf("p=%p\n", p);
  printf("pp=%p\n", pp);
/*
 *   pp (int**)         p (int*)          nr (int)
 * +--------+         +--------+         +--------+
 * | address| ------->|address | ------> |  10    |
 * +--------+         +--------+         +--------+
 */

  fun1(p);
  printf("fun1(p) = %d\n", *p);
  fun(pp);
  printf("fun(pp) = %d\n", **pp);

  int var1 = 0;
  const int* p2 = &var1;
  // ptr -> ptr -> const int
  const int** pp2 = &p2;
  printf("*pp2 = %d\n", **pp2);
  //**pp2 = 18;
/*
 *   pp2 (int**)        p2 (int*)         nr (const int)
 * +--------+         +--------+         +-----------+
 * | address| ------->|address | ------> |       10  |
 * +--------+         +--------+         +-------===-+
 */
  return 0;
}


