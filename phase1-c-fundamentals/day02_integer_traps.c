#include <stdint.h>
#include <stdio.h>

// 1. Show promotion: return sum as uint8_t and as int32_t, print both
void promotion_trap(uint8_t a, uint8_t b);

// 2. Show sign mixing: reproduce the sensor/offset bug, print
//    what -5 becomes as uint32_t and what the comparison evaluates to
void sign_mixing_trap(void);

// 3. Show sizeof for char, short, int, long, long long
void sizeof_trap(void);

void promotion_trap(uint8_t a, uint8_t b) {
    printf("input a as uint8_t %d\n", a);
    printf("input b as uint8_t %d\n", b);
    uint8_t uint8_t_sum = a + b;
    uint32_t uint32_t_sum = a + b;
    printf("the value of a + b is truncated into uint8_t: %d\n", uint8_t_sum);
    printf("the value of a + b is truncated into uint32_t: %d\n", uint32_t_sum);
}
    
void sign_mixing_trap(void) {
    int32_t offset = -5;
    uint32_t sensor = 3;
    printf("sensor + offset > 8 evaluates to: %d\n", (sensor + offset) > 8);
    printf("because -5 as uint32_t is: %u\n", (uint32_t)offset);
}

void sizeof_trap(void) {
    printf("the sizeof of char: %zu\n", sizeof(char));
    printf("the sizeof of short: %zu\n", sizeof(short));
    printf("the sizeof of int: %zu\n", sizeof(int));
    printf("the sizeof of long: %zu\n", sizeof(long));
    printf("the sizeof of long long: %zu\n", sizeof(long long));
}

int main(void) {
    printf("promotion trap\n");
    promotion_trap(200, 100);
    printf("sign mixing trap\n");
    sign_mixing_trap();
    printf("sizeof trap\n");
    sizeof_trap();
    return 0;
}