; irq_stubs.s
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

extern kisr_handler

; %1 = IRQ number (0–15)
; %2 = interrupt vector (0x20–0x2F)
%macro IRQ_COMMON 2
irq%1:
    cli

    push 0              ; no error code
    push %2             ; interrupt number (vector)
    pusha               ; push general registers

    push es
    push ds

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp            ; pointer to registers_t
    call kisr_handler
    add esp, 4          ; clean pointer

    pop es
    pop ds
    popa
    add esp, 8          ; pop int_no + err_code
    sti
    iret
%endmacro


; IRQ 0–15 = vecteurs 0x20–0x2F
IRQ_COMMON 0, 0x20
IRQ_COMMON 1, 0x21
IRQ_COMMON 2, 0x22
IRQ_COMMON 3, 0x23
IRQ_COMMON 4, 0x24
IRQ_COMMON 5, 0x25
IRQ_COMMON 6, 0x26
IRQ_COMMON 7, 0x27
IRQ_COMMON 8, 0x28
IRQ_COMMON 9, 0x29
IRQ_COMMON 10, 0x2A
IRQ_COMMON 11, 0x2B
IRQ_COMMON 12, 0x2C
IRQ_COMMON 13, 0x2D
IRQ_COMMON 14, 0x2E
IRQ_COMMON 15, 0x2F
