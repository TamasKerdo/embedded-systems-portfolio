# Day 6: Memory Segments

## Context

I am following a structured 26-week embedded systems learning plan (3 days/week,
3-4 hours/day). Currently on **Phase 1, Day 6**.

**5-phase plan:**
- Phase 1 (Weeks 1-3): C/C++ refresh + toolchain
- Phase 2 (Weeks 4-9): Bare-metal + RTOS on STM32F4 Discovery
- Phase 3 (Weeks 10-15): Embedded Linux + Yocto on Raspberry Pi 4
- Phase 4 (Weeks 16-21): Automotive/safety-critical (AUTOSAR, ISO 26262, CAN-FD, UDS)
- Phase 5 (Weeks 22-26): Interview preparation

**Hardware:** Waveshare STM32F4DISCOVERY (STM32F407, Cortex-M4), LA1010 logic
analyzer, CP2102 USB-UART, GY-BME280 sensor, breadboard, multimeter

**Environment:** Docker (arm-none-eabi-gcc 13.2, cppcheck, cmake), VS Code Dev
Container, clangd, CI pipeline (cppcheck → ASAN/UBSAN → ARM build), Extreme C
by Kamran Amini

**Days 1-5 covered:**
- Day 1-2: Integer types, promotion, signed/unsigned mixing, platform-dependent
  widths, two's complement
- Day 3: Pointers & memory — pointer arithmetic, array decay, const correctness,
  common pointer bugs, memory addressing (1 address = 1 byte, little-endian)
- Day 4: Structs & memory layout — padding, alignment, packed, bit fields,
  register maps, volatile, read-modify-write pattern
- Day 5: Functions, stack & calling conventions — stack frames, pass by value vs
  const pointer, static inline, stack overflow risk, Cortex-M4 registers (r0-r15)

**Portfolio:** `phase1/day01_types.c` through `phase1/day05_stack.c` — CI green

**Day 6 topic:** Memory segments — `.text`, `.rodata`, `.data`, `.bss`,
heap vs stack, `static` keyword in depth

## Tutor Instructions

- Teach with explanation + example code + exercise for each part, in that order
- Never give me solution code — give hints only and force me to think
- At the end of the day give me a substantial summary challenge — no solution,
  hints only
- Regularly challenge my understanding with questions — don't just present
  material, make me prove I understood it
- Check my memory of previous days when concepts connect
- When I write code, review it and point out bugs without fixing them — make me
  find the fix
- Push me to verify everything with the toolchain (size, nm, objdump)

## Summary

_Added after session:_

- Covered `.text`, `.rodata`, `.data`, `.bss` — verified with
  `arm-none-eabi-size` and `arm-none-eabi-nm`
- Learned that `const` globals go to `.rodata` (flash, zero RAM cost),
  non-`const` globals go to `.data` (costs flash + RAM) or `.bss` (zero-init,
  RAM only)
- Understood three meanings of `static`: internal linkage, persistent local,
  and the nm symbol case difference (uppercase = global, lowercase = local)
- Investigated struct padding: Buffer struct = 72 bytes not 70 due to 2-byte
  padding before `uint32_t count` (alignment from Day 4 confirmed)
- Explored `objdump -s -j .data` and little-endian byte layout in the dump
- Summary challenge: implemented a circular buffer data logger with correct
  section placement, `static` encapsulation, and pointer-based output parameters
- Portfolio file: `phase1/day06_segments.c` — CI green