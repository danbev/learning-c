#define __wu __attribute__((__warn_unused_result__))

__wu int doit() {
  return 18;
}

int main(int argc, char** argv) {
  doit();
  return 0;
}
