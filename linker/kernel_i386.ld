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
        _data_start = .;
        *(.data)
        *(.data.*)
        _data_end = .;
    }

    .bss : ALIGN(4096) {
        _bss_start = .;
        *(COMMON)
        *(.bss)
        *(.bss.*)
        _bss_end = .;
    }

    .padding : {
        *(.padding)
    }

    /* @brief Start of the early heap used in the early_allocator section. */
    _kernel_early_heap_start_sym = .;

    /* Reserve 4 KiB for early heap (size of early heap) */
    /* INFO: If you changed this you absolutely need to modify the define : KERNEL_MEMORY_EARLY_PAGE_SIZE
     *       Located in the file : early_allocator.h
     */
    . += 4096;

    /* @brief End of the early heap */
    _kernel_early_heap_end_sym = .;
}
