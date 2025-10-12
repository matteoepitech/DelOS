; boot.s
org 0x7c00

; ======================================================
; REAL MODE
; ======================================================
[bits 16]

KERNEL_LOCATION equ 0x10000
KERNEL_BASE_POINTER equ 0x90000
CODE_SEG        equ code_descriptor - GDT_Start ; = 0x08 which is 1 * 8, so the CPU know it's the index number 1 for the code segment
DATA_SEG        equ data_descriptor - GDT_Start ; = 0x10 which is 2 * 8, so the CPU know it's the index number 2 for the data segment

; BIOS set dl to the loaded disk ID, so we copy it
mov [BOOT_DISK_ID], dl

; setup real mode stack and registers
xor ax, ax
mov ds, ax
mov es, ax
mov ss, ax
mov sp, 0x7c00
mov bp, sp

; load kernel and store it on KERNEL_LOCATION
; in real mode, we need to use segment:offset addressing
; 0x10000 = 0x1000:0x0000
mov ax, 0x1000          ; segment for kernel location
mov es, ax              ; set ES segment
xor bx, bx              ; offset = 0, so ES:BX = 0x1000:0x0000 = 0x10000

mov ah, 0x02            ; read storage from disk interuption id
mov al, 0x14            ; we will read 20 sector (MAY INCREASE THIS, this is the kernel ~ size)
mov ch, 0x00            ; cylinder number 0
mov dh, 0x00            ; head number 0
mov cl, 0x02            ; sector number 2 (after the bootsector)
mov dl, [BOOT_DISK_ID]  ; drive number, the same as the bootsector owner
int 0x13                ; interuption for reading disk storage

; change the video mode
mov ah, 0x0             ; change video mode interuption id
mov al, 0x3             ; desired video mode (text mode)
int 0x10                ; interuption for changing the video mode from the BIOS

; switch to protected mode
cli                     ; disable material interupts
lgdt [GDT_Descriptor]   ; load the global descriptor table into the register GDTR
mov eax, cr0            ; copy the cr0 = control register 0
or eax, 0b1             ; set the PE (protected enable) first bit to 1
mov cr0, eax            ; set back the control register

jmp dword CODE_SEG:start_protected_mode ; do a far jump to load the code segment
jmp $                                   ; should never goes here

; GDT : flat model of memory
;  -> data and code are in the same space and extended on the whole memory
; the global descriptor table should be at the end of the real mode code
%include "extra/gdt.s"

; ======================================================
; PROTECTED MODE
; ======================================================
[bits 32]

start_protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, KERNEL_BASE_POINTER
    mov esp, ebp

    jmp KERNEL_LOCATION ; jump to the kernel

; ======================================================
; DATA
; ======================================================
BOOT_DISK_ID db 0

; ======================================================
; BOOT SIGNATURE
; ======================================================
times 510-($-$$) db 0
dw 0xaa55
