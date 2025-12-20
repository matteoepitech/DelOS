; a20.s
; see https://wiki.osdev.org/A20_Line
; this method is actually the : Fast A20 Gate
; maybe we should swap to the old one for more compatibility but for now it's fine
; this file is included

in al, 0x92
test al, 2
jnz done
or al, 2
and al, 0xFE
out 0x92, al

done:
