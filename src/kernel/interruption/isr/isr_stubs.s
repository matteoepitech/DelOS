; isr_stubs.s
; all interruption service routine
global isr0
global isr1
global isr13

; isr_handler intermediate handler
extern kisr_handler

; create a macro fo all isr without error code
%macro ISR_NOERR 1
isr%1:
    pusha             ; save all registers
    push 0            ; fake err_code
    push %1           ; interrupt number
    call kisr_handler ; intermediate handler
    add esp, 8        ; we go before the 2 pushs since these push are not bypassed in the handler
    popa              ; pop back all registers
    iret              ; interruption return
%endmacro

; all isr without error code
ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 13

; all isr with error code
; ...
