; boot.s
ORG 0x7c00

; ======================================================
; REAL MODE
; ======================================================
[BITS 16]

CODE_SEG equ code_descriptor - GDT_Start ; = 0x08 which is 1 * 8, so the CPU know it's the index number 1 for the code segment
DATA_SEG equ data_descriptor - GDT_Start ; = 0x10 which is 2 * 8, so the CPU know it's the index number 2 for the data segment

mov [BOOT_DISK_ID], dl  ; BIOS set dl to the loaded disk ID, so we copy it
cli                     ; disable material interupts
lgdt [GDT_Descriptor]   ; load the global descriptor table into the register GDTR
mov eax, cr0            ; copy the cr0 = control register 0
or eax, 0b1             ; set the PE (protected enable) first bit to 1
mov cr0, eax            ; set back the control register

jmp dword CODE_SEG:start_protected_mode ; do a far jump to load the code segment
jmp $                                   ; should never goes here

; flat model of memory
; data and code are in the same space and extended on the whole memory
; the global descriptor table should be at the end of the real mode code
GDT_Start:
    null_descriptor:
        dq 0x00
    code_descriptor:
        dw 0xffff
        dw 0x00
        db 0x00
        db 0b10011010
        db 0b11001111
        db 0x00
    data_descriptor:
        dw 0xffff
        dw 0x00
        db 0x00
        db 0b10010010
        db 0b11001111
        db 0x00
GDT_End:
GDT_Descriptor:
    dw GDT_End - GDT_Start - 1  ; size
    dd GDT_Start                ; start

; ======================================================
; PROTECTED MODE
; ======================================================
[BITS 32]

start_protected_mode:
    mov al, 'A'
    mov ah, 0x0f
    mov [0xb8000], ax
    jmp $

; ======================================================
; DATA
; ======================================================
msg_start db "Bootloader started...", 13, 10, 0

BOOT_DISK_ID db 0

; ======================================================
; BOOT SIGNATURE
; ======================================================
times 510-($-$$) db 0
dw 0xaa55
