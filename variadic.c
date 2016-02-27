#include <stdio.h>
#include <stdarg.h>

void print(int n,...);

int main(void) {
    print(10, 20, 30);
    return 0;
}

void print(int n, ...) {
    va_list ap;
    va_start(ap, n);
    printf("%d, %d, %d\n", n, va_arg(ap, int), va_arg(ap, int));
    va_end(ap);
}
