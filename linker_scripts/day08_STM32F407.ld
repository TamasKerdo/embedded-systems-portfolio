MEMORY {
  FLASH : ORIGIN = 0x08000000, LENGTH = 1024K
  RAM : ORIGIN = 0x20000000, LENGTH = 128K
}

ENTRY(Reset_Handler)

SECTIONS {
  .isr_vector : {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Keep vector table even if unused */
    . = ALIGN(4);
  } > FLASH

  .text : {
    *(.text*)
  } > FLASH

  .rodata : {
    *(.rodata*)
  } > FLASH

  .data : {
    _sdata = .;
    *(.data*)
    _edata = .;
  } > RAM AT > FLASH

  _sidata = LOADADDR(.data);

  .bss : {
    _sbss = .;
    *(.bss*)
    _ebss = .;
  } > RAM

  _estack = ORIGIN(RAM) + LENGTH(RAM);
}