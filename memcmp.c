#include <stdio.h>
#include <strings.h>

int main(void) {
    char *str1 = "abcd";
    char *str2 = "abcd";
    int r = memcmp(str1, str2, 5);
    if (r == 0) {
        printf("%s was equal to %s\n", str1, str2);
    } else if (r > 0) { 
        printf("%s was greater than %s\n", str1, str2);
    } else {
        printf("%s was less than %s\n", str1, str2);
    }
    return 0;
}
