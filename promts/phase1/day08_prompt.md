# Day 8: Vector Table Deep-Dive + Preprocessor & Build System

## Context

I am following a structured 26-week embedded systems learning plan (3 days/week,
3-4 hours/day). Currently on **Phase 1, Day 8**.

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

**Days 1-7 covered:**
- Day 1-2: Integer types, promotion, signed/unsigned mixing, platform-dependent
  widths, two's complement
- Day 3: Pointers & memory — pointer arithmetic, array decay, const correctness,
  memory addressing (1 address = 1 byte, little-endian)
- Day 4: Structs & memory layout — padding, alignment, packed, bit fields,
  register maps, volatile, read-modify-write pattern
- Day 5: Functions, stack & calling conventions — stack frames, pass by value vs
  const pointer, static inline, Cortex-M4 registers (r0-r15), AAPCS
- Day 6: Memory segments — `.text`, `.rodata`, `.data`, `.bss`, heap vs stack,
  `static` keyword (internal linkage + persistent locals), circular buffer
  implementation, verified with `arm-none-eabi-size` and `arm-none-eabi-nm`
- Day 7: Function pointers & callbacks — declaration-follows-usage, typedef for
  function pointers, function-to-pointer decay, callback pattern with NULL
  guards, jump tables (static const, .rodata placement, indexed indirect call),
  state machines (designated initializers, NUM_STATES trick), connection from
  jump table to vector table

**Portfolio:** `phase1/day01_types.c` through `phase1/day07_function_pointers.c` — CI green

## Day 8 Topic Part 1: Vector Table Deep-Dive (carried over from Day 7)

**What to cover (~1 hour):**

1. **The vector table in flash** — confirm via `objdump` and `arm-none-eabi-nm`
   that the vector table is an array of function pointers placed at the very
   start of flash by the linker script.
2. **`.isr_vector` section** — how the linker script places it via `KEEP()` and
   `. = ORIGIN(FLASH);`, why `KEEP()` is needed (preventing dead-code elimination).
3. **Cortex-M4 vector table layout** — vector 0 = initial stack pointer (special),
   vector 1 = Reset_Handler, vector 3 = HardFault_Handler, vector 15 = SysTick.
4. **VTOR register** — Vector Table Offset Register; how the CPU finds the table
   on reset, and how it can be relocated (bootloader use case).
5. **Connecting Day 7 to hardware** — when an interrupt fires, the CPU literally
   does the same indexed-indirect-call (`BLX`) you saw in your jump table
   `objdump` output, with the NVIC supplying the index.

**Expected output:** a short markdown file `phase1/day08_vector_table.md` with
the `objdump`/`nm` output, screenshots/snippets of the linker script section,
and a one-paragraph summary of how interrupts dispatch via the vector table.

## Day 8 Topic Part 2: Preprocessor Depth (~2 hours)

**What to cover:**

1. **The four phases of the preprocessor** — `#include`, `#define`, conditional
   compilation, line/file tracking. Run `gcc -E` to see the output.
2. **`#define` vs `const` vs `enum`** — extending Day 7's brief table; when each
   wins on storage, type safety, scope, and debuggability.
3. **Macros vs inline functions** — `MAX(a, b)` macro pitfalls (double evaluation,
   no type safety, operator precedence), why `static inline` is usually better,
   when macros are still right (compile-time string generation, conditional
   compilation, X-macros).
4. **Stringification (`#`) and token pasting (`##`)** — what they do, the canonical
   "debug print with variable name" use case, and the X-macro pattern for
   keeping an enum and its string names in sync.
5. **Header guards and `#pragma once`** — what each does, which is portable,
   which embedded HALs prefer.
6. **Conditional compilation patterns** — `#ifdef`, `#if defined()`, feature
   flags, platform gating (`STM32F407xx` vs `STM32F411xx`), and how this
   shows up in real HAL code.

**Expected portfolio output:** `phase1/day08_preprocessor.c` demonstrating
stringification, token pasting, an X-macro for an enum with stringified names,
and a sensible header guard pattern.

## Tutor Instructions — Please Follow These Carefully

- I am on **Day 8**, not Day 7
- Teach with explanation + example code + exercise for each part, in that order
- **Never give me solution code** — give hints only and force me to think
- At the end of the day give me a substantial summary challenge — no solution,
  hints only. A good fit for today: an X-macro-based command table that combines
  jump tables (Day 7) with stringification (Day 8), so commands are kept in
  sync between their dispatch function pointer and their human-readable name
- Regularly challenge my understanding with questions — don't just present
  material, make me prove I understood it
- **Check my memory of previous days** when concepts connect — for example
  when discussing macros vs inline, ask what I remember about `.text` placement
  from Day 6; when discussing the vector table, ask what I remember about jump
  tables and the `BLX` instruction from Day 7
- When I write code, review it and point out bugs without fixing them — make me
  find the fix
- Push me to verify everything with the toolchain (`size`, `nm`, `objdump`,
  `gcc -E` to see preprocessor output)
- Keep me thinking, not just reading
- Day 7 was long (5 parts, ran into Day 8); aim to keep Day 8 in scope. If we
  run out of time, the X-macro summary challenge can slip to Day 9 — Part 1
  (vector table) and Part 2 (preprocessor basics through stringification) are
  the priority.