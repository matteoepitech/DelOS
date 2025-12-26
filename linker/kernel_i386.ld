ENTRY(_start)
OUTPUT_FORMAT(binary)

KERNEL_VIRTUAL_BASE = 0xC0000000;
KERNEL_PHYSICAL_BASE = 0x00100000;

SECTIONS
{
    . = KERNEL_VIRTUAL_BASE + KERNEL_PHYSICAL_BASE;

    .text : AT(KERNEL_PHYSICAL_BASE) ALIGN(4096) {
        *(.text)
        *(.text.*)
    }

    .rodata : AT(ADDR(.rodata) - KERNEL_VIRTUAL_BASE) ALIGN(4096) {
        *(.rodata)
        *(.rodata.*)
    }

    .data : AT(ADDR(.data) - KERNEL_VIRTUAL_BASE) ALIGN(4096) {
        _data_start = .;
        *(.data)
        *(.data.*)
        _data_end = .;
    }

    .bss : AT(ADDR(.bss) - KERNEL_VIRTUAL_BASE) ALIGN(4096) {
        _bss_start = .;
        *(COMMON)
        *(.bss)
        *(.bss.*)
        _bss_end = .;
    }

    .padding : AT(ADDR(.padding) - KERNEL_VIRTUAL_BASE) {
        *(.padding)
    }

    /* Early heap section */
    _kernel_early_heap_start_sym = .;
    . += 1024 * 256;
    _kernel_early_heap_end_sym = .;

    _bss_start_phys = _bss_start - KERNEL_VIRTUAL_BASE;
    _bss_end_phys = _bss_end - KERNEL_VIRTUAL_BASE;
}
