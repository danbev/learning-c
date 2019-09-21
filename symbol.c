#include <stdio.h>
/*
 * clang -o symbol symbol.cc
 *
 * See the libraries that were linked:
 * $ otool -L symbol
 *
 *
 * $ nm symbol
 */
int globalVar = 30;

int doit() {
    return 10;
}

int main(void) {
    int n = doit();
    printf("n = %d\n", n);
}
