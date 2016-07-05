#include <stdio.h>

/**
 * Basic example of verifying my understanding of macros
 *
 * There are basically 3 type the preprocessor handles:
 * 1) Directives
 * Tell the preprocessor to include files, skip parts of the file
 * 2) Constants
 * 3) Macros
 */

// example of a function like macro:
#define DO_IT() \
    printf("DO_IT macro\n");

// macro with argument example:
#define PRINT_STR(str) \
    printf("PRINT_STR str=%s\n", str);

// multi-line macro that can be used in if statements that don't
// use braces. More information can be found in the WONT_WORK_IN_IF
// macro below.
#define DO(name)                        \
    do {                                \
        printf("first = %s\n", name);   \
        printf("second = %s\n", name);  \
    } while (0)
    
// Remember that a macro is replaced in the code by the preprocessor,
// and if you use this macro in an if statement (without braces) this 
// will cause the preprocessor to include both lines and the else statement
// will not line up with the if. One solution is to use a do{ ... } while(0)
// to do this. 
#define WONT_WORK_IN_IF(name)           \
    printf("first = %s\n", name);       \
    printf("second = %s\n", name);       

// Just a macro I found which I was not sure how it worked.
#define STRUCT_MACRO(name, type)        \
struct prefix_ ## name {                  \
    struct type *inner;                 \
}

#define STRINGIFY(s) #s

#define C_CTOR(fn)                                               \
  static void fn(void) __attribute__((constructor));             \
  static void fn(void)

static void hello() {
     printf("hello from __attribute__\n");
}

C_CTOR(beve_init) {
    hello();
}

#define EMPTY

int main() {
    DO_IT();
    PRINT_STR("bajja");
    if (true) 
        DO("something");
        //WONT_WORK_IN_IF("somthing")
    else
        printf("not doing it...\n");

    struct sometype {
        const char* name;
    };

    STRUCT_MACRO(test_name, sometype);
    struct prefix_test_name st;
    st.inner->name = "testing";
    printf("%s\n", st.inner->name);

    const char* str = STRINGIFY(bajja);
    printf("%s\n", str);

    EMPTY int i = 10;
    return 0;
}
