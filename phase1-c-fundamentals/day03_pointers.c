/**
 * phase1/day03_pointers.c
 *
 * Day 3 - Pointers & Memory in C
 * Topics: pointer arithmetic, array decay, const correctness, common bugs
 *
 * Build (host, with ASAN/UBSAN):
 *   gcc -Wall -Wextra -fsanitize=address,undefined -o day03 day03_pointers.c
 *
 * Build (ARM cross-compile):
 *   arm-none-eabi-gcc -Wall -Wextra -o day03.elf day03_pointers.c
 */

#include <stdint.h>
#include <stdio.h>

/*
 * 1. POINTER ARITHMETIC — stride depends on pointed-to type
 */

static void demo_pointer_arithmetic(void)
{
  printf("=== 1. Pointer Arithmetic ===\n");

  uint8_t arr8[4] = {10, 20, 30, 40};
  uint32_t arr32[4] = {10, 20, 30, 40};

  uint8_t *p8 = arr8;
  uint32_t *p32 = arr32;

  printf("uint8_t  pointer stride:\n");
  for (int i = 0; i < 4; i++)
  {
    printf("  p8[%d]  addr=%p  value=%u\n", i, (void *)p8, *p8);
    p8++;
  }

  printf("uint32_t pointer stride:\n");
  for (int i = 0; i < 4; i++)
  {
    printf("  p32[%d] addr=%p  value=%u\n", i, (void *)p32, *p32);
    p32++;
  }

  /*
   * Expected output: consecutive uint8_t addresses differ by 1 byte,
   * consecutive uint32_t addresses differ by 4 bytes.
   * This is because ptr + 1 advances by sizeof(*ptr) bytes.
   */
  printf("\n");
}

/*
 * 2. ARRAY DECAY — array is not a pointer, but decays to one
 */

static void demo_array_decay(void)
{
  printf("=== 2. Array Decay ===\n");

  uint8_t buffer[4] = {10, 20, 30, 40};
  uint8_t *p = buffer; /* decay: no & needed, points to buffer[0] */

  /* array indexing and pointer arithmetic are equivalent */
  printf("  buffer[2]    = %u\n", buffer[2]);
  printf("  *(p + 2)     = %u\n", *(p + 2));

  /* sizeof reveals the difference */
  printf("  sizeof(buffer) = %zu  (array knows its full size)\n", sizeof(buffer));
  printf("  sizeof(p)      = %zu  (pointer is just an address)\n", sizeof(p));

  printf("\n");
}

/*
 * 3. CONST CORRECTNESS
 *
 *   const uint8_t *p       → value is read-only, pointer can move
 *   uint8_t * const p      → pointer is fixed, value can change
 *   const uint8_t * const p → both are read-only
 */

/**
 * read_sum - demonstrates a read-only buffer parameter.
 *
 * const uint8_t *data promises the caller: this function will
 * never modify the contents of the buffer. The compiler enforces it.
 * You will see this pattern in every STM32 HAL transmit API.
 */
static uint32_t read_sum(const uint8_t *data, uint16_t len)
{
  uint32_t sum = 0;
  for (uint16_t i = 0; i < len; i++)
  {
    sum += data[i];
    /* data[i] = 0;  <-- compiler error: assignment of read-only location */
  }
  return sum;
}

static void demo_const_correctness(void)
{
  printf("=== 3. Const Correctness ===\n");

  uint8_t buffer[4] = {10, 20, 30, 40};

  /* const uint8_t *p — pointer can move, value cannot be changed via p */
  const uint8_t *p = buffer;
  p++;           /* OK: moving the pointer */
  /* *p = 99; */ /* would be a compiler error */
  printf("  read via const ptr: %u\n", *p);

  uint32_t sum = read_sum(buffer, 4);
  printf("  sum via read-only function: %u\n", sum);

  printf("\n");
}

/*
 * 4. CORRECT fill() — fixed uint8_t overflow bug from exercise
 *
 * Bug: using uint8_t for both count parameter and loop index
 * means passing 256 wraps to 0 before the function runs,
 * and i overflows to 0 at 255 causing an infinite loop.
 *
 * Fix: use uint16_t for both count and loop index.
 */

static void fill(uint8_t *dst, uint8_t val, uint16_t count)
{
  for (uint16_t i = 0; i < count; i++)
  {
    *dst = val;
    dst++;
  }
}

static void demo_fill(void)
{
  printf("=== 4. Correct fill() ===\n");

  uint8_t buffer[256];
  fill(buffer, 0xFF, 256);

  /* spot-check a few positions */
  printf("  buffer[0]   = 0x%02X\n", buffer[0]);
  printf("  buffer[127] = 0x%02X\n", buffer[127]);
  printf("  buffer[255] = 0x%02X\n", buffer[255]);

  printf("\n");
}

/*
 * 5. WARMUP REVISITED — infinite loop via uint8_t loop counter
 *
 * The original loop:
 *   for (uint8_t i = 0; i < 256; i++)
 * is an infinite loop because i overflows 255 → 0,
 * so i < 256 is always true.
 *
 * Fix: use uint16_t for the index.
 */

static void demo_warmup_fixed(void)
{
  printf("=== 5. Warmup Fixed ===\n");

  uint8_t buffer[256];

  /* fixed: uint16_t index can reach 256 without overflowing */
  for (uint16_t i = 0; i < 256; i++)
  {
    buffer[i] = (uint8_t)i;
  }

  printf("  buffer[0]   = %u\n", buffer[0]);
  printf("  buffer[127] = %u\n", buffer[127]);
  printf("  buffer[255] = %u\n", buffer[255]);

  printf("\n");
}

/*
 * main
 */

int main(void)
{
  demo_pointer_arithmetic();
  demo_array_decay();
  demo_const_correctness();
  demo_fill();
  demo_warmup_fixed();

  printf("All demos complete. ASAN/UBSAN should report no errors.\n");
  return 0;
}
