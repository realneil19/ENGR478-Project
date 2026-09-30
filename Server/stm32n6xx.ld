/* Memory layout for STM32N657 / STM32N647 */
MEMORY
{
  /* System AXI SRAM / Internal Execution RAM */
  SRAM (xrw) : ORIGIN = 0x20000000, LENGTH = 512K
}

ENTRY(Reset_Handler)

SECTIONS
{
  /* Vector table at start of execution region */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } > SRAM

  /* Program code and read-only constants */
  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } > SRAM

  /* Initialized static data */
  .data :
  {
    . = ALIGN(4);
    *(.data)
    *(.data*)
    . = ALIGN(4);
  } > SRAM

  /* Uninitialized static data (BSS) */
  .bss :
  {
    . = ALIGN(4);
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
  } > SRAM
}