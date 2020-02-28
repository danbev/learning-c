#include <stdlib.h>

struct Something {
    int x;
    int y;
};

int main(int argc, char** argv) {
    struct Something* s = malloc(sizeof(struct Something));
    s->x = 1;
    s->y = 2;
    return 0;
}
