#include <stdio.h>

/**
 * In general, to declare a pointer to a particular kind of function, you can 
 * first write a prototype for a regular function of the desired kind and then 
 * replace the function name with an expression in the form (*name).
 */
void doit() {
    printf("do it...\n");
}

void doSomething(void (*func)()) {
    func();
}

int main(void) {
    // just like you have to declare int* you have to specify the type for a
    // function pointer:
    void (*printit)() = doit;
    // the parentheses around *printit are required to acount for operator 
    // precedence. Parentheses have higher priority than *, so 
    // *printit() would mean a function that returns a pointer, and
    // (*printit)()
    doSomething(printit);
    return 0;
}
