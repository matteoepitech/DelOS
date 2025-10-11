; boot.s
BITS 16
ORG 0x7c00

; ----------------------------------------
; void _start(void)
; ----------------------------------------
_start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00
    mov bp, sp

    mov si, msg_start
    call print_string
    
    call enable_a20

    xor cx, cx

.wait_key:
    mov ah, 0
    int 0x16
    cmp al, 13
    je .print_key
    push ax
    inc cx
    jmp .wait_key

.print_key:
    test cx, cx
    jz .done
    dec cx
    mov bx, sp
    add bx, cx
    add bx, cx
    mov al, byte [bx]
    mov ah, 0x0e
    int 0x10
    jmp .print_key

.done:
    jmp $

; ----------------------------------------
; void print_string(char *string)
;
; Parameters:
;   - si = string address
; ----------------------------------------
print_string:
    lodsb
    test al, al
    jz .done
    mov ah, 0x0e
    xor bh, bh
    int 0x10
    jmp print_string

.done:
    ret

; ----------------------------------------
; void enable_a20(void)
; ----------------------------------------
enable_a20:
    mov ah, 0x24        ; "Enable A20" BIOS function
    int 0x15
    jnc .done
    jmp .fail

.done:
    mov si, msg_a20_ok
    call print_string
    ret

.fail:
    mov si, msg_a20_ko
    call print_string
    ret


; ======================================================
; DATA
; ======================================================
msg_start db "Bootloader started...", 13, 10, 0
msg_a20_ok db "A20 line enabled!", 13, 10, 0
msg_a20_ko db "A20 line failed!", 13, 10, 0

; ======================================================
; BOOT SIGNATURE
; ======================================================
times 510-($-$$) db 0
dw 0xaa55
