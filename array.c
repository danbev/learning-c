#include <stdio.h>

int main(int argc, char** argv) {
    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr = arr;
    printf("arr size = %lu\n", sizeof(arr)/sizeof(int));

    // ptr will point to the first element of arr
    printf("ptr: %p\n", ptr);
    printf("arr: %p\n", arr);
    printf("&arr[0]: %p\n", &arr[0]);

    printf("*ptr: %d\n", *ptr);
    printf("ptr[0]: %d\n", ptr[0]);
    printf("arr[0]: %d\n", arr[0]);
    printf("prt+1: %d\n", *ptr+1);
    printf("arr+1: %d\n", *arr+1);

    int mul[2][3] = { {1, 2, 3}, {4, 5, 6} }; 
    // this will be aligned in memory something like:
    // mul[0][0] = 1
    // mul[0][1] = 2
    // mul[0][2] = 3
    // mul[1][0] = 4
    // mul[1][1] = 5
    // mul[1][3] = 6
    // mul[1][1] = 5
    for (int i = 0; i < 2; i++) {
        // size will be 12 as each 'row' has 3 elements of size 4 bytes each
        printf("&mul[%d]: %p sizeof(mul[%d]): %lu\n", i, &mul[i], i, sizeof(mul[i]));
    }
    // so we are declaring and initializing an array of char pointers which 
    // langs points to.
    char *langs[] = {"Go", "C", "C++", "JavaScript", "java"};
    char **expert[] = {&langs[4]};
    for (int i = 0; i < sizeof(expert)/sizeof(char*); i++) {
        printf("Expert level in %s\n", *expert[i]);
    }
    char **inter[3];
    inter[0] = &langs[1];
    inter[1] = &langs[2];
    inter[2] = &langs[3];
    for (int i = 0; i < sizeof(inter)/sizeof(char*); i++) {
        printf("Intermediate level in %s\n", *inter[i]);
    }
    // so both expert and inter contain pointers into the langs array.
    // we can update it and they will be updated.
    *&langs[4] = "Java";
    printf("Updated *&langs[4] to %s\n", *&langs[4]);
    printf("Updated *expert[0] to %s\n", *expert[0]);
    return 0;
}
