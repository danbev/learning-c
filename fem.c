#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct something {
  int age;
  char n[];
  //char n[1];
};

int main(int argc, char** argv) {
  printf("Flexible Array Member example\n");

  const char* n = "bajja";
  struct something* s = (struct something*) malloc(sizeof (struct something) + sizeof(char [strlen(n)]));
  memcpy(s->n, n, strlen(n));
  printf("s->n: %s\n", s->n);

  free(s);
  return 0;
}
