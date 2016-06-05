#include <strings.h>
#include <stdio.h>

int main(int argc, char **argv) {
    // as string literal would most often be assigned to the literal pool
    // so using the string literal multiple times in a program will use 
    // one single entry in the pool
    const char *str = "bajja";
    const char *str2 = "bajja";
    printf("&str: \t %p\n", str);
    printf("&str2:\t %p\n", str);

    // an array of size 6 (one for the NUL character). 
    // the initialization will copy the characters into the
    // array
    char arr[] = "array";
    printf("strlen(arr)=%lu\n", strlen(arr));
    return 0;
}
