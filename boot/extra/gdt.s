; GDT : flat model of memory
;  -> data and code are in the same space and extended on the whole memory
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
