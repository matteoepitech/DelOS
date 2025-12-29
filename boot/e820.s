; e820.s

; e820 data is written by the bootloader in low memory; keep in sync with pmm.h
%ifndef KE820_INFO_ADDR
    %define KE820_INFO_ADDR 0x0500
%endif

%ifndef KE820_BUFFER_ADDR
    %define KE820_BUFFER_ADDR 0x0600
%endif

%ifndef KE820_ENTRY_SIZE
    %define KE820_ENTRY_SIZE 0x18
%endif

%ifndef KE820_MAX_ENTRIES
    %define KE820_MAX_ENTRIES 32
%endif
; -- stop syncing here --

xor ax, ax
mov es, ax
mov di, KE820_BUFFER_ADDR
mov dword [KE820_INFO_ADDR], 0
mov dword [KE820_INFO_ADDR + 4], KE820_BUFFER_ADDR

xor ebx, ebx
xor bp, bp

.e820_loop:
    mov eax, 0xE820
    mov edx, 0x534D4150         ; 'SMAP'
    mov ecx, KE820_ENTRY_SIZE
    int 0x15

    jc .done
    cmp eax, 0x534D4150
    jne .done

    inc bp
    add di, KE820_ENTRY_SIZE

    cmp bp, KE820_MAX_ENTRIES
    jae .done

    test ebx, ebx
    jne .e820_loop

.done:
    xor eax, eax
    mov ax, bp
    mov dword [KE820_INFO_ADDR], eax
