#include <stdio.h>

typedef struct {
  int age;
} Base;

typedef struct {
  Base base;
  int nr;
} Derived;

void printBase(Base *base) {
  printf("Base: age=%d\n", base->age);
}

int main(void) {
  Derived d; 
  d.base.age = 40;
  d.nr = 100;
  Base *b = (Base*) &d;

  printBase(b);
  printBase((Base *) &d);

  printf("%p: %d, nr=%d\n", &d.base, d.base.age, d.nr);
  printf("%p: %d\n", &(*b), b->age);
  return 0;
}

