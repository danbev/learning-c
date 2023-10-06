#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void) {
    float smallest_values[10];
    uint32_t float_bits = 0x00800000;  // Binary representation of the smallest normalized value: 2^-126

    for (int i = 0; i < 10; ++i) {
        memcpy(&smallest_values[i], &float_bits, sizeof(float));
        float_bits += 0x00000001;  // Increment the fraction part by 1 to get the next value
    }

    // Output the values
    for (int i = 0; i < 10; ++i) {
        printf("%.8e\n", smallest_values[i]);
    }

    return 0;
}

