; kernel_entry.s

; ======================================================
; PROTECTED MODE
; ======================================================
[bits 32]

[extern kmain]
[extern kvmm_init]
[extern kearly_malloc_init]
[extern kgdt_init]
[extern kvmm_disable_identity_mapping]
[extern kpmm_init]

[extern __data_start]
[extern __data_end]
[extern __bss_start_phys]
[extern __bss_end_phys]
[extern __kernel_stack_end]

; KERNEL_VIRTUAL_BASE = The base of the address of the kernel in the virtual address space
KERNEL_VIRTUAL_BASE equ 0xC0000000

; _start definition global (our entry point)
global _start

_start:
    mov edi, __bss_start_phys
    jmp zero_bss

; reset the BSS section (block started symbol)
zero_bss:
    cmp edi, __bss_end_phys
    jge setup_paging
    mov byte [edi], 0
    inc edi
    jmp zero_bss

setup_paging:
    call kearly_malloc_init
    call kpmm_init
    call kvmm_init
    lea ecx, [higher_half]
    jmp ecx

higher_half:
    mov esp, __kernel_stack_end
    mov ebp, esp

    call kgdt_init
    call kvmm_disable_identity_mapping

enter_kernel:
    call kmain
    jmp $       ; should never goes here
