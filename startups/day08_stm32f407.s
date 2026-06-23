.syntax unified
.cpu cortex-m4
.thumb

/*--- Global ISR Handler Declarations ---*/
.global Reset_Handler
.global NMI_Handler
.global HardFault_Handler
.global MemManage_Handler
.global BusFault_Handler
.global UsageFault_Handler
.global SVC_Handler
.global DebugMon_Handler
.global PendSV_Handler
.global SysTick_Handler

/*--- Vector Table ---*/
.section .isr_vector,"a",%progbits
.type g_pfnVectors, %object
.size g_pfnVectors, .-g_pfnVectors
g_pfnVectors:
    .word _estack                 @ 0: Initial Stack Pointer
    .word Reset_Handler           @ 1: Reset Handler
    .word NMI_Handler             @ 2: NMI Handler
    .word HardFault_Handler       @ 3: HardFault Handler
    .word MemManage_Handler       @ 4: Memory Manage Handler
    .word BusFault_Handler        @ 5: Bus Fault Handler
    .word UsageFault_Handler      @ 6: Usage Fault Handler
    .word 0                       @ 7: Reserved
    .word 0                       @ 8: Reserved
    .word 0                       @ 9: Reserved
    .word 0                       @ 10: Reserved
    .word SVC_Handler             @ 11: SVCall Handler
    .word DebugMon_Handler        @ 12: Debug Monitor Handler
    .word 0                       @ 13: Reserved
    .word PendSV_Handler          @ 14: PendSV Handler
    .word SysTick_Handler         @ 15: SysTick Handler

/*--- Reset Handler ---*/
.section .text
.thumb_func
Reset_Handler:
    /* Initialize .data and .bss */
    ldr r0, =_sdata
    ldr r1, =_edata
    ldr r2, =_sidata
    b 2f
1:
    ldr r3, [r2], #4
    str r3, [r0], #4
2:
    cmp r0, r1
    blo 1b

    /* Zero .bss */
    ldr r0, =_sbss
    ldr r1, =_ebss
    movs r2, #0
3:
    str r2, [r0], #4
    cmp r0, r1
    blo 3b

    /* Call main() */
    bl main
    /* Should never reach here */
    b .

/*--- Default ISR Handlers ---*/
.thumb_func
NMI_Handler:
    b .

.thumb_func
HardFault_Handler:
    b .

.thumb_func
MemManage_Handler:
    b .

.thumb_func
BusFault_Handler:
    b .

.thumb_func
UsageFault_Handler:
    b .

.thumb_func
SVC_Handler:
    b .

.thumb_func
DebugMon_Handler:
    b .

.thumb_func
PendSV_Handler:
    b .

.thumb_func
SysTick_Handler:
    b .
