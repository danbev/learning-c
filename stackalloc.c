#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Something {
    int x;
    int y;
    int* lock;
};

int main(int argc, char** argv) {
  int nr = 10;
  struct Something s = {1, 2, &nr};
  struct Something* s_ptr = malloc(sizeof(struct Something));
  s_ptr->x = 4;
  s_ptr->y = 5;
  s_ptr->lock = &nr;
  printf("&s_ptr.lock: %p\n", s_ptr->lock);

  struct Something stack_allocated;
  stack_allocated = *s_ptr;
  printf("stack_allocated.x: %d\n", stack_allocated.x);
  printf("stack_allocated.y: %d\n", stack_allocated.y);
  printf("stack_allocated.lock: %d\n", *stack_allocated.lock);
  printf("&stack_allocated.lock: %p\n", stack_allocated.lock);

  printf("Now call memset on s_ptr.\n\n");
  int* tmp_lock = s_ptr->lock;
  memset(s_ptr, 0, sizeof(*s_ptr));

  printf("Stack allocated:\n");
  printf("stack_allocated.x: %d\n", stack_allocated.x);
  printf("stack_allocated.y: %d\n", stack_allocated.y);
  printf("stack_allocated.lock: %d\n", *stack_allocated.lock);
  printf("&stack_allocated.lock: %p\n", stack_allocated.lock);

  printf("\nHeap allocated: \n");
  printf("s_ptr->x: %d\n", s_ptr->x);
  printf("s_ptr->y: %d\n", s_ptr->y);
  printf("s_ptr->lock: %p\n", s_ptr->lock);

  printf("\nStack pointer to lock: \n");
  printf("tmp_lock: %p\n", tmp_lock);
  printf("*tmp_lock: %d\n", *tmp_lock);
  return 0;
}
