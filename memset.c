#include <stdio.h>
#include <string.h>

int main(void) {
  char str[10];
  strcpy(str, "Bajja");
  printf("%s\n", str);

  memset(str, '$', 5);
  printf("%s\n", str);

  return 0;
}
