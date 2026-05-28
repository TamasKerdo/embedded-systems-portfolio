
/**
 * phase1/day05_stack.c
 *
 * Day 5 - Functions, Stack & Calling Conventions
 * Topics: pass by value vs pointer, static inline, stack overflow risk
 *
 * Build (host, with ASAN/UBSAN):
 *   gcc -Wall -Wextra -fsanitize=address,undefined -o day05 day05_stack.c
 *
 * Build (ARM cross-compile):
 *   arm-none-eabi-gcc -Wall -Wextra -o day05.elf day05_stack.c
 */

#include <stdint.h>
#include <stdio.h>

/*
 * 1. PASS BY VALUE VS PASS BY POINTER
 *
 * Passing a struct by value copies the entire struct onto the
 * stack. Passing by const pointer pushes only 4 bytes (the
 * address) on STM32, regardless of struct size.
 *
 * Always prefer const pointer for structs in embedded code.
 */

typedef struct
{
  uint32_t a;
  uint32_t b;
  uint32_t c;
} MyStruct; /* 12 bytes */

static void pass_by_value(MyStruct s)
{
  /* sizeof(s) gives the full struct size — 12 bytes pushed onto stack */
  printf("By value   — bytes pushed onto stack: %zu\n", sizeof(s));
}

static void pass_by_pointer(const MyStruct *s)
{
  /* sizeof(s) gives pointer size — 4 bytes on STM32, 8 on host */
  /* sizeof(*s) gives the actual struct size */
  printf("By pointer — bytes pushed onto stack: %zu\n", sizeof(s));
  printf("             actual struct size:       %zu\n", sizeof(*s));
}

static void demo_pass_by(void)
{
  printf("=== 1. Pass By Value vs Pointer ===\n");

  MyStruct s = {.a = 1, .b = 2, .c = 3};

  pass_by_value(s);
  pass_by_pointer(&s);

  printf("\n");
}

/*
 * 2. STATIC INLINE
 *
 * static        → visible only in this translation unit,
 *                 prevents name collisions across files
 * inline        → hints compiler to replace call with function
 *                 body, eliminating stack frame overhead
 *
 * Common pattern in STM32 HAL for small utility functions.
 */

static inline uint32_t clamp(uint32_t val, uint32_t max)
{
  return val > max ? max : val;
}

static void demo_static_inline(void)
{
  printf("=== 2. Static Inline ===\n");

  printf("clamp(10, 5)  = %u\n", clamp(10, 5));
  printf("clamp(3, 5)   = %u\n", clamp(3, 5));
  printf("clamp(5, 5)   = %u\n", clamp(5, 5));

  printf("\n");
}

/*
 * 3. STACK OVERFLOW RISK
 *
 * The STM32F407 default stack is typically 4KB. A large local
 * array can silently overflow it — no exception by default,
 * just silent memory corruption.
 *
 * BAD — 4096 bytes on the stack, likely overflows:
 *
 *   void bad(void) {
 *       uint8_t buf[4096];
 *       memset(buf, 0xFF, sizeof(buf));
 *   }
 *
 * GOOD — static moves the buffer into .bss (global RAM),
 * not the stack. Zero stack cost, persists between calls:
 *
 *   void good(void) {
 *       static uint8_t buf[4096];
 *       memset(buf, 0xFF, sizeof(buf));
 *   }
 *
 * Use the ARM stack usage report to verify frame sizes:
 *   arm-none-eabi-gcc -fstack-usage day05_stack.c
 */

static void demo_stack_overflow_risk(void)
{
  printf("=== 3. Stack Overflow Risk ===\n");

  /* safe: static buffer lives in .bss, not on the stack */
  static uint8_t buf[4096];
  buf[0] = 0xFF;
  buf[4095] = 0xFF;

  printf("static buf[0]    = 0x%02X\n", buf[0]);
  printf("static buf[4095] = 0x%02X\n", buf[4095]);
  printf("stack cost of this buffer: 0 bytes (static → .bss)\n");

  printf("\n");
}

int main(void)
{
  demo_pass_by();
  demo_static_inline();
  demo_stack_overflow_risk();

  printf("All demos complete. ASAN/UBSAN should report no errors.\n");
  return 0;
}