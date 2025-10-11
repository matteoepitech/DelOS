; boot.s
BITS 16
ORG 0x7c00

; BIOS put into dl the disk number. So we save it back.
mov [BOOT_DISK], dl

xor ax, ax
mov ds, ax
mov es, ax
mov ss, ax
mov sp, 0x7c00
mov bp, sp

mov si, msg_start
call print_string

call enable_a20

mov bx, 0x7e00 ; where to store data 0x0000:0x7E00 = 0x7E00
mov ah, 2 ; read storage from disk
mov al, 1 ; sector to read count
mov ch, 0 ; cylinder
mov dh, 0 ; head
mov cl, 2 ; sector
mov dl, [BOOT_DISK] ; drive
int 0x13

mov si, 0x7e00
call print_string

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

BOOT_DISK db 0

; ======================================================
; BOOT SIGNATURE
; ======================================================
times 510-($-$$) db 0
dw 0xaa55

times 512 db 'A'
