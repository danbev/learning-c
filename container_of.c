#include <stdio.h>

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

struct s {
  int one;
  char two;
};

/*
 * This function is intended to simulate a function that is passed a 
 * value for which it needs to get the struct that the value is a member
 * of.
 */
void something(char* value) {
  struct s* sp = container_of(value, struct s, two);
  printf("struct for two:%p\n", sp);
  printf("sp.two: %c\n", sp->two);
}

int main(int argc, char** argv) {
  // the following is a gnu extension  called brace-group within expression
  // where the compiler will evaluate the complete block and use the last
  // value in the block:
  int nr = ( { int x = 10; x + 4; } );
  printf("nr:%d\n", nr);
  // Notice that this is used in the container_of macro, it returns the 
  // value from the last statement.
  //
  int x = 1;
  typeof(x) y = 2;
  printf("%d %d\n", x, y);
  

  int* p = &((struct s*)0)->one;
  char* p2 = &((struct s*)0)->two;
  printf("%p\n", p);
  printf("%p\n", p2);

  struct s s1;
  struct s* sp = container_of(&s1.two, struct s, two);

  struct s s2 = {1, 'a'};
  printf("s=%p\n", &s2);
  printf("s.two=%c\n", s2.two);
  something(&s2.two);

  return 0;
}
