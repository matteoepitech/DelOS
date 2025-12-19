; kernel_entry.s

; ======================================================
; PROTECTED MODE
; ======================================================
[bits 32]
[extern kmain]
[extern _data_start]
[extern _data_end]
[extern _bss_start]
[extern _bss_end]

; _start definition global (our entry point)
global _start

_start:
    mov edi, _bss_start
    jmp zero_bss

; reset the BSS section (block started symbol)
zero_bss:
    cmp edi, _bss_end
    jge enter_kernel
    mov byte [edi], 0
    inc edi
    jmp zero_bss

enter_kernel:
    call kmain  ; call the main kernel function
    jmp $       ; should never goes here
