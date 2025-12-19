ENTRY(_start)
OUTPUT_FORMAT(binary)

SECTIONS
{
    . = 0x10000;

    .text : ALIGN(4096) {
        *(.text)
        *(.text.*)
    }

    .rodata : ALIGN(4096) {
        *(.rodata)
        *(.rodata.*)
    }

    .data : ALIGN(4096) {
        *(.data)
        *(.data.*)
    }

    .bss : ALIGN(4096) {
        *(COMMON)
        *(.bss)
        *(.bss.*)
    }

    .padding : {
        *(.padding)
    }

    /* @brief Start of the early heap used in the early_allocator section. */
    _kernel_start_early_heap = .;
}
