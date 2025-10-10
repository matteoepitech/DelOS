; boot.s - Bootloader real mode (16 bits)
BITS 16
ORG 0x7C00

; definitions
global _start

; _start symbol
_start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00    ; move stack pointer to 0x7C00
   
    cld               ; set DF flag to 0
    mov si, msg
    call print_string
    
    jmp $

; print_string symbol
print_string:
    lodsb             ; load a byte from si in al and increment si by 1 if DF is 0
    test al, al       ; al & al
    jz .done
    mov ah, 0x0E      ; function id (write teletype character on screen)
    xor bh, bh        ; set the page number to 0 for the write
    int 0x10          ; interupt 17 for managing visual and video mode
    jmp print_string

.done:
    ret

msg db "DelOS booted!", 13, 10, 0

; set 512 bytes object file with MBR signature
times 510-($-$$) db 0
dw 0xAA55
