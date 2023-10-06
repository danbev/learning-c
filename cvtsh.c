#include <stdio.h>
#include <immintrin.h>

#include <stdio.h>
#include <stdint.h>
#include <string.h>

void print_binary_float(float value) {
    uint32_t bit_representation;
    memcpy(&bit_representation, &value, sizeof(value));

    for (int i = 31; i >= 0; --i) {
        printf("%d", (bit_representation >> i) & 1);
        if (i == 31) printf(" ");  // Separate the sign bit
        if (i == 23) printf(" ");  // Separate the exponent
    }
    printf("\n\n");
}

/*
(gdb) p ii
$135 = 5

$134 = 2.98023224e-07
(gdb) x /t  &f

0x7fffffffa1f4:	00110100101000000000000000000000

0 01101001 01000000000000000000000
*/

static float table_f32_f16[100];

int main() {
    for (int i = 0; i <= 100; i++) {
      unsigned short half = i;
      float single = _cvtsh_ss(half); // cvt=convert t=to scalar halt(sh) scalar single (ss)
      printf("half = %d single-precision value: %.23E %.23f\n", i, single, single);
      print_binary_float(single);
      table_f32_f16[i] = single;
    }

    for (int i = 0; i <= 100; i++) {
      printf("table_f32_f16[%d] = %.7E\n", i, table_f32_f16[i]);
    }

    uint16_t src = 1.0f;
    uint16_t dest;
    memcpy(&dest, &src, sizeof(uint16_t));

    printf("dest = %d\n", dest);
    float f = table_f32_f16[dest];
    printf("lookup %.7E\n", f);

    return 0;
}
