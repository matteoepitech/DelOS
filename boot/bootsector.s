; boot.s
org 0x7c00

; ======================================================
; REAL MODE
; ======================================================
[bits 16]

%ifndef KERNEL_SECTORS
    ; fallback value, normally replaced at build time with the real kernel size
    %define KERNEL_SECTORS 0x30
%endif

; KERNEL_LOCATION = The base physical address of the start of the kernel in the RAM
KERNEL_LOCATION      equ 0x100000
KERNEL_BASE_POINTER  equ 0x090000
CODE_SEG             equ code_descriptor - GDT_Start ; = 0x08 which is 1 * 8, so the CPU know it's the index number 1 for the code segment
DATA_SEG             equ data_descriptor - GDT_Start ; = 0x10 which is 2 * 8, so the CPU know it's the index number 2 for the data segment
MAX_SECTORS_PER_READ equ 127                         ; max sectors per call (64KB / 512)

; BIOS set dl to the loaded disk ID, so we copy it
mov [BOOT_DISK_ID], dl

; setup real mode stack and registers
xor ax, ax
mov ds, ax
mov es, ax
mov ss, ax
mov sp, 0x7c00
mov bp, sp

; using INT 0x13 extended read (LBA mode) which is much simpler and no CHS limits
; this works on all modern BIOS and emulators (QEMU, VirtualBox, etc.)
mov word [.dap_segment], 0x1000     ; initial segment for buffer
mov word [.dap_offset], 0x0000      ; offset = 0
mov dword [.dap_lba_low], 1         ; LBA sector 1 (sector 0 = bootsector, so kernel starts at 1)
mov dword [.dap_lba_high], 0
mov word [.sectors_left], KERNEL_SECTORS

.read_loop:
    mov ax, [.sectors_left]
    test ax, ax
    jz .read_done

    ; calculate sectors to read this pass
    cmp ax, MAX_SECTORS_PER_READ
    jbe .use_ax
    mov ax, MAX_SECTORS_PER_READ

.use_ax:
    mov [.dap_count], ax
    ; call INT 13h extended read (AH=42h)
    mov ah, 0x42
    mov dl, [BOOT_DISK_ID]
    mov si, .dap              ; DS:SI = pointer to DAP
    int 0x13
    jc .disk_error
    ; update sectors left
    mov ax, [.dap_count]
    sub [.sectors_left], ax
    ; advance LBA
    add [.dap_lba_low], ax
    adc word [.dap_lba_high], 0
    ; advance buffer segment (sectors * 512 / 16 = sectors * 32)
    shl ax, 5
    add [.dap_segment], ax
    jmp .read_loop

.disk_error:
    mov si, .error_msg
    call .print_string
    jmp $

; Disk Address Packet (DAP) for INT 13h extended read
.dap:
    db 0x10             ; size of DAP (16 bytes)
    db 0                ; reserved
.dap_count:     dw 0    ; number of sectors to read
.dap_offset:    dw 0    ; buffer offset
.dap_segment:   dw 0    ; buffer segment
.dap_lba_low:   dd 0    ; LBA low 32 bits
.dap_lba_high:  dd 0    ; LBA high 32 bits

.sectors_left:  dw 0
.error_msg:     db "Disk read error!", 0

.print_string:
    lodsb
    or al, al
    jz .print_done
    mov ah, 0x0e
    int 0x10
    jmp .print_string
.print_done:
    ret

.read_done:

%include "e820.s"       ; get the RAM (e820 entries) from BIOS
%include "a20.s"        ; enable the A20 bit line

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

check_a20:
    pushad
    mov edi, 0x112345    ; odd megabyte address (1MB + 0x12345)
    mov esi, 0x012345    ; even megabyte address (0x12345)

    mov eax, [esi]
    push eax
    mov eax, [edi]
    push eax

    mov dword [esi], 0x00000000
    mov dword [edi], 0xFFFFFFFF

    mov eax, [esi]
    mov ebx, [edi]
    cmp eax, ebx

    pop eax
    mov [edi], eax
    pop eax
    mov [esi], eax

    popad
    je shutdown_now      ; If equal, then A20 is OFF

    ; weird stuff to load the kernel from 0x10000 to 0x100000
    mov esi, 0x00010000
    mov edi, 0x00100000
    mov ecx, KERNEL_SECTORS
    shl ecx, 7
    rep movsd

    jmp KERNEL_LOCATION

shutdown_now:
    mov dx, 0x604
    mov ax, 0x2000
    out dx, ax
    hlt

; ======================================================
; DATA
; ======================================================
BOOT_DISK_ID db 0

; ======================================================
; BOOT SIGNATURE
; ======================================================
times 510-($-$$) db 0
dw 0xaa55
