; kernel_entry.s

; ======================================================
; PROTECTED MODE
; ======================================================
[bits 32]
[extern kmain]
[extern kvmm_init]
[extern _data_start]
[extern _data_end]
[extern _bss_start_phys]
[extern _bss_end_phys]

; KERNEL_VIRTUAL_BASE = The base of the address of the kernel in the virtual address space
KERNEL_VIRTUAL_BASE equ 0xC0000000

; _start definition global (our entry point)
global _start

_start:
    mov edi, _bss_start_phys
    jmp zero_bss

; reset the BSS section (block started symbol)
zero_bss:
    cmp edi, _bss_end_phys
    jge setup_paging
    mov byte [edi], 0
    inc edi
    jmp zero_bss

setup_paging:
    call kvmm_init
    lea ecx, [higher_half]
    jmp ecx

higher_half:
    add esp, KERNEL_VIRTUAL_BASE
    add ebp, KERNEL_VIRTUAL_BASE

enter_kernel:
    call kmain
    jmp $       ; should never goes here
