# Day 7: Function Pointers & Callback Patterns

## Context

I am following a structured 26-week embedded systems learning plan (3 days/week,
3-4 hours/day). Currently on **Phase 1, Day 7**.

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

**Days 1-6 covered:**
- Day 1-2: Integer types, promotion, signed/unsigned mixing, platform-dependent
  widths, two's complement
- Day 3: Pointers & memory — pointer arithmetic, array decay, const correctness,
  common pointer bugs, memory addressing (1 address = 1 byte, little-endian)
- Day 4: Structs & memory layout — padding, alignment, packed, bit fields,
  register maps, volatile, read-modify-write pattern
- Day 5: Functions, stack & calling conventions — stack frames, pass by value vs
  const pointer, static inline, stack overflow risk, Cortex-M4 registers (r0-r15)
- Day 6: Memory segments — `.text`, `.rodata`, `.data`, `.bss`, heap vs stack,
  `static` keyword (internal linkage + persistent locals), circular buffer
  implementation, verified with `arm-none-eabi-size` and `arm-none-eabi-nm`,
  struct padding, little-endian objdump output

**Portfolio:** `phase1/day01_types.c` through `phase1/day06_segments.c` — CI green

## Day 7 Topic: Function Pointers & Callback Patterns

**What to cover today:**

1. **Function pointer syntax** — declaring, assigning, and calling function
   pointers. Why the syntax looks the way it does.

2. **typedef for function pointers** — making the syntax readable, which is
   how real firmware code is written.

3. **Callback pattern** — passing a function pointer as a parameter so the
   caller decides the behavior. Common in drivers and HAL layers.

4. **Jump tables** — an array of function pointers, used in embedded for
   dispatching commands, state machines, and protocol handlers.

5. **ISR vector table connection** — how the Cortex-M4 vector table is literally
   an array of function pointers in flash, and how this connects to everything
   above.

**Expected portfolio output:** `phase1/day07_function_pointers.c`

## Tutor Instructions — Please Follow These Carefully

- I am on **Day 7**, not Day 6
- Teach with explanation + example code + exercise for each part, in that order
- **Never give me solution code** — give hints only and force me to think
- At the end of the day give me a substantial summary challenge (like the
  circular buffer from Day 6) — no solution, hints only
- Regularly challenge my understanding with questions — don't just present
  material, make me prove I understood it
- **Check my memory of previous days** when concepts connect — for example if
  alignment comes up, ask me what I remember from Day 4; if sections come up,
  ask me what I remember from Day 6
- When I write code, review it and point out bugs without fixing them — make me
  find the fix
- Push me to verify everything with the toolchain (`size`, `nm`, `objdump`)
- Keep me thinking, not just reading

See you on Day 7! 💪