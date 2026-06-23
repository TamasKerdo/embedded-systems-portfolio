/*
arm-none-eabi-gcc -c startups/day08_stm32f407.s -o ./startup.o                                                                             // compile the startup file
arm-none-eabi-gcc -c phase1-c-fundamentals/day07_state_machine.c -o ./day08_state_machine.o                                                // compile the c code
arm-none-eabi-gcc -T linker_scripts/day08_STM32F407.ld -nostdlib -ffreestanding startup.o day08_state_machine.o -o day08_state_machine.elf // link together
arm-none-eabi-nm -n day08_state_machine.elf | grep -E "Reset_Handler|NMI_Handler|HardFault_Handler|_estack"                                // check
  08000040 T Reset_Handler                                                                                                                 // .text
  08000068 T NMI_Handler
  0800006a T HardFault_Handler
  20020000 B _estack                                                                                                                       // .bss

arm-none-eabi-objdump -s -j .isr_vector day08_state_machine.elf

day08_state_machine.elf:     file format elf32-littlearm

Contents of section .isr_vector:                                                                                                           // vector table
  8000000 00000220 41000008 69000008 6b000008  ... A...i...k...
  8000010 6d000008 6f000008 71000008 00000000  m...o...q.......
  8000020 00000000 00000000 00000000 73000008  ............s...
  8000030 75000008 00000000 77000008 79000008  u.......w...y...
*/