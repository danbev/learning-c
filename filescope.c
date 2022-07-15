#include <stddef.h>

static const size_t buffer_len = 100;
// buffer_len is still a variable because in C const means read-only and does
// not mean that the momory location cannot be changed.
int buffer[buffer_len];

int main(int argc, char** argv) {
  return 0;
}
