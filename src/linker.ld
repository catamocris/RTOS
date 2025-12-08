/* src/linker.ld */

MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
    RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 128K
}

/* top of stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    /* Vector table la începutul FLASH */
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH

    /* Cod și date constante */
    .text :
    {
        *(.text*)
        *(.rodata*)
    } > FLASH

    /* Date inițializate (RAM încărcat din FLASH) */
    .data : AT(ADDR(.text) + SIZEOF(.text))
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > RAM

    /* Adresa din FLASH de unde copiăm .data */
    _sidata = LOADADDR(.data);

    /* Date neinițializate (.bss) – zero la startup */
    .bss :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > RAM
}
