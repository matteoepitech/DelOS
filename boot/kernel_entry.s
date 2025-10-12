; kernel_entry.s

; ======================================================
; PROTECTED MODE
; ======================================================
[bits 32]
[extern kmain]

; _start definition global (our entry point)
global _start

_start:
    call kmain  ; call the main kernel function
    jmp $       ; should never goes here
