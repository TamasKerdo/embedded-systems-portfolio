#include <stdint.h>

/*
 NOTE: .data section shown by objdump is the FLASH copy (load address).
 At boot, startup code copies this verbatim into SRAM before main() runs.
 Cost: flash (initializer) + SRAM (runtime) for every .data variable.


arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -c ./phase1-c-fundamentals/day06_memory.c -o ./day06_memory.o
arm-none-eabi-size day06_memory.o

text    data     bss     dec     hex     filename
526     256      256    1038     40e     day06_memory.o
*/

const uint8_t a[256];                       // -> .rodata (const but uninitialized — compiler zero-inits)
const uint8_t b[256] = {0, 1, 2 /* ... */}; // -> .rodata (const initialized — stays in flash)

uint8_t c[256] = {0};                 // -> 256 bytes .bss  (explicitly zero-initialized global)
uint8_t d[256] = {0, 1, 2 /* ... */}; // -> 256 bytes .data (initialized global)
char e[5] = "Hello";                  // -> 5 bytes   .data (initialized global)
int f = 17618;                        // 0x44d2                    // -> 4 bytes   .data (initialized global)

int main(void)
{
  uint8_t e = 12; // -> stack (local variable, exists only during main() execution)
                  // not visible in objdump — allocated at runtime via SP adjustment
  return 0;
}

/*
arm-none-eabi-nm day06_memory.o
00000000 R a
00000100 R b //256 bytes later
00000000 B c
00000000 D d
00000100 D e
00000108 D f // Hello -> 5 byes + 3 padding
00000000 T main

arm-none-eabi-objdump -s -j .data day06_memory.o

-s       -> objdump: show the full content of the chosen section
-j .data -> show the content of the .data section

day06_memory.o:     file format elf32-littlearm

Contents of section .data:
 0000 00010200 00000000 00000000 00000000  ................ -> Address Data_0 Data_1 Data_2 Data_3 ASCII_representation
 0010 00000000 00000000 00000000 00000000  ................
 0020 00000000 00000000 00000000 00000000  ................
 0030 00000000 00000000 00000000 00000000  ................
 0040 00000000 00000000 00000000 00000000  ................
 0050 00000000 00000000 00000000 00000000  ................
 0060 00000000 00000000 00000000 00000000  ................
 0070 00000000 00000000 00000000 00000000  ................
 0080 00000000 00000000 00000000 00000000  ................
 0090 00000000 00000000 00000000 00000000  ................
 00a0 00000000 00000000 00000000 00000000  ................
 00b0 00000000 00000000 00000000 00000000  ................
 00c0 00000000 00000000 00000000 00000000  ................
 00d0 00000000 00000000 00000000 00000000  ................
 00e0 00000000 00000000 00000000 00000000  ................
 00f0 00000000 00000000 00000000 00000000  ................
 0100 48656c6c 6f000000 d2440000           Hello....D..     -> 0x44d2 (Decimal, Big Endian: 17618), d244 (Decimal Little Endian)
 */

/* Memory addressing

  0000 XX...... ........ ........ ........
  0001 ..XX.... ........ ........ ........
  0002 ....XX.. ........ ........ ........
  0003 ......XX ........ ........ ........
  000F ........ ........ ........ ......XX
  0010 XX...... ........ ........ ........
  ...
*/