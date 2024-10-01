#include <stdio.h>

#define MAX_ITEMS 5

struct item {
    int id;
    char name[20];
    float price;
};

struct inventory {
    struct item items[MAX_ITEMS];
    int count;
};

int main() {
    // Initialize the inventory
    struct inventory inventory = {
        //.items = {{ 1, "First Item", 9.99 }},
        .items = { { 9 } },
        .count = 1
    };

    // Print all items
    for (int i = 0; i < MAX_ITEMS; i++) {
        printf("item %d:\n", i);
        printf("  id: %d\n", inventory.items[i].id);
        printf("  name: %s\n", inventory.items[i].name);
        printf("  price: %.2f\n\n", inventory.items[i].price);
    }

    return 0;
}
