ENTRY(_start)
OUTPUT_FORMAT(binary)

KERNEL_VIRTUAL_BASE = 0xC0000000;
KERNEL_PHYSICAL_BASE = 0x00100000;

SECTIONS
{
    . = KERNEL_VIRTUAL_BASE + KERNEL_PHYSICAL_BASE;
    
    __kernel_start = .;
    __kernel_physical_start = KERNEL_PHYSICAL_BASE;
    __kernel_virtual_start = KERNEL_VIRTUAL_BASE + KERNEL_PHYSICAL_BASE;
    
    .text : AT(KERNEL_PHYSICAL_BASE) ALIGN(4096) {
        __text_start = .;
        *(.text)
        *(.text.*)
        __text_end = .;
    }
    
    .rodata : AT(ADDR(.rodata) - KERNEL_VIRTUAL_BASE) ALIGN(4096) {
        __rodata_start = .;
        *(.rodata)
        *(.rodata.*)
        __rodata_end = .;
    }
    
    .data : AT(ADDR(.data) - KERNEL_VIRTUAL_BASE) ALIGN(4096) {
        __data_start = .;
        _data_start = .;
        *(.data)
        *(.data.*)
        __data_end = .;
        _data_end = .;
    }
    
    .bss : AT(ADDR(.bss) - KERNEL_VIRTUAL_BASE) ALIGN(4096) {
        __bss_start = .;
        _bss_start = .;
        *(COMMON)
        *(.bss)
        *(.bss.*)
        __bss_end = .;
        _bss_end = .;
    }
    
    .padding : AT(ADDR(.padding) - KERNEL_VIRTUAL_BASE) {
        *(.padding)
    }
    
    /* Early heap section */
    __kernel_early_heap_start = .;
    _kernel_early_heap_start_sym = .;
    . += 1024 * 256;
    __kernel_early_heap_end = .;
    _kernel_early_heap_end_sym = .;
    
    __kernel_end = .;
    __kernel_virtual_end = .;
    __kernel_physical_end = . - KERNEL_VIRTUAL_BASE;
    
    __kernel_size = __kernel_end - __kernel_start;
    __kernel_size_pages = (__kernel_size + 4095) / 4096;
    
    _bss_start_phys = _bss_start - KERNEL_VIRTUAL_BASE;
    _bss_end_phys = _bss_end - KERNEL_VIRTUAL_BASE;
    
    __text_start_phys = __text_start - KERNEL_VIRTUAL_BASE;
    __text_end_phys = __text_end - KERNEL_VIRTUAL_BASE;
    __rodata_start_phys = __rodata_start - KERNEL_VIRTUAL_BASE;
    __rodata_end_phys = __rodata_end - KERNEL_VIRTUAL_BASE;
    __data_start_phys = __data_start - KERNEL_VIRTUAL_BASE;
    __data_end_phys = __data_end - KERNEL_VIRTUAL_BASE;
    __bss_start_phys = __bss_start - KERNEL_VIRTUAL_BASE;
    __bss_end_phys = __bss_end - KERNEL_VIRTUAL_BASE;
}
