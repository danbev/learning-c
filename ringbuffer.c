#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

#define _min(A, B) ((A) < (B) ? (A) : (B))
#define _max(A, B) ((A) > (B) ? (A) : (B))

typedef struct {
  uint8_t* buf;
  size_t nr_elements;
  size_t size;
  size_t first;
  size_t len;
} ringbuf;

int init_buf(ringbuf* rb, size_t nr_elements, size_t size) {
  printf("size of buf: %zu\n", size * nr_elements);
  //rb->buf = malloc(size * nr_elements);
  rb->buf = calloc(nr_elements, size);
  rb->nr_elements = nr_elements;
  rb->size = size;
  rb->first = 0;
  rb->len = 0;
  return 0;
}

int full(ringbuf* rb) {
  printf("full len=%zu, nr_elements=%zu\n", rb->len, rb->nr_elements);
  return rb->len == rb->nr_elements;
}

void free_buf(ringbuf* rb) {
  if (rb != NULL) {
    free(rb->buf);
  }
}

void print_binary(size_t n){
  while (n) {
    if (n & 1)
        printf("1");
    else
        printf("0");

    n >>= 1;
  }
  printf("\n");
}

void* push_front(ringbuf* rb) {
  /// Remember that size_t is unsigned so it never represents a negative value
  size_t f = (rb->first-1);
  size_t s = (rb->nr_elements-1);
  printf("push_front f=%zu, s=%zu, new_first=%zu\n", f, s, (f & s));
  //print_binary(f);
  //print_binary(s);
  //print_binary(f & s);
  rb->first = (rb->first -1 ) & (rb->nr_elements -1 ); 
  rb->len = _min(rb->nr_elements, rb->len + 1); 
  printf("push_front index=%zu\n", (rb->first * rb->size));
  // The buf array contains elements of size (malloc(size * nr_elements))
  // So if the new first is 2 we need to multiply that with the 
  return (void*) &rb->buf[rb->first * rb->size];
}

void* push_back(ringbuf* rb) {
  size_t offset = (rb->first + rb->len) & (rb->nr_elements -1);
  if (rb->len == rb->nr_elements) {
    rb->first = (rb->first + 1) & (rb->nr_elements -1);
  } else {
    ++rb->len;
  }
  return (void*) &rb->buf[offset * rb->size];
}

void* get(ringbuf* rb, size_t offset) {
  offset = (rb->first + offset) & (rb->nr_elements -1);
  return &rb->buf[offset * rb->size];
}

void print_buf(uint8_t* buf, size_t len) {
  for (int i = 0; i < len; i++) {
    printf("%hhu", buf[i]);
  }
  printf("\n");
}

int main(int argc, char** argv) {
  ringbuf rb;
  init_buf(&rb, 4, sizeof(int)); 
  printf("is rb full: %d\n", full(&rb));
  /*
   * 0              15
   * 0000000000000000
   */

  printf("Ringbuffer size=%zu, len=%zu\n", rb.size, rb.len);

  // Get a pointer from the ringbuffer 
  int* int_ptr = push_front(&rb);
  *int_ptr = 4;
  print_buf(rb.buf, 4 * sizeof(int));
  /*
   * 0              15
   * 0000000000004000
   * So push_front returns a pointer to the 12 index in the buf array.
   */
  printf("Ringbuffer size=%zu, len=%zu\n", rb.size, rb.len);
  int* getptr = get(&rb, 0);
  printf("is rb full: %d\n", full(&rb));
  printf("getptr=%d\n", *getptr);

  int* int_ptr2 = push_front(&rb);
  *int_ptr2 = 3;
  print_buf(rb.buf, 4 * sizeof(int));
  /*
   * 0                15
   * 0000 0000 6000 4000
   * Notice that the second call to push_front returned a pointer to the
   * 8 index in the buf array.
   */
  printf("Ringbuffer size=%zu, len=%zu\n", rb.size, rb.len);
  int* int_ptr3 = push_front(&rb);
  *int_ptr3 = 2; 
  print_buf(rb.buf, 4 * sizeof(int));
  printf("is rb full: %d\n", full(&rb));

  int* int_ptr4 = push_front(&rb);
  *int_ptr4 = 1; 
  print_buf(rb.buf, 4 * sizeof(int));
  printf("is rb full: %d\n", full(&rb));
  // 1000200030004000

  printf("is rb full: %d\n", full(&rb));
  int* int_ptr5 = push_front(&rb);
  *int_ptr5 = 5; 
  print_buf(rb.buf, 4 * sizeof(int));
  // 1000200030005000
  printf("is rb full: %d\n", full(&rb));

  ringbuf rb2;
  init_buf(&rb2, 4, sizeof(int)); 
  int* bptr1 = push_back(&rb2);
  printf("*bptr1=%d\n", *bptr1);
  *bptr1 = 12; 
  print_buf(rb2.buf, 4 * sizeof(int));

  free_buf(&rb);
  free_buf(&rb2);
  return 0;
}
