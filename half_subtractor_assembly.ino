; ============================================================
;  Half-Subtractor — AVR ATmega328P Assembly
;  Registers: PIND (input port D), PORTB (output port B)
;  Pin Map  : PD2=A, PD3=B, PB4=D(LED), PB5=X(LED)
;  Compiled : avr-gcc -mmcu=atmega328p -O2
; ============================================================

#include <avr/io.h>

.section .text
.global main

; ── Initialisation ──────────────────────────────────────────
init:
    in   r16, DDRD        ; Load Port D direction register
    andi r16, 0b11110011  ; Clear bits 2 and 3 (inputs)
    out  DDRD, r16

    in   r16, DDRB        ; Load Port B direction register
    ori  r16, 0b00110000  ; Set bits 4 and 5 (outputs)
    out  DDRB, r16

    in   r16, PORTD
    andi r16, 0b11110011  ; Disable internal pull-ups on PD2, PD3
    out  PORTD, r16

; ── Main processing loop ─────────────────────────────────────
main:
    in   r16, PIND        ; Read Port D (contains A at bit2, B at bit3)

    ; ── Extract A (PD2) → r17 bit 0 ─────────────────────────
    mov  r17, r16
    andi r17, 0b00000100  ; Isolate PD2
    lsr  r17              
    lsr  r17              ; r17 = A (0 or 1)

    ; ── Extract B (PD3) → r18 bit 0 ─────────────────────────
    mov  r18, r16
    andi r18, 0b00001000  ; Isolate PD3
    lsr  r18
    lsr  r18
    lsr  r18              ; r18 = B (0 or 1)

    ; ── Compute D = A XOR B ──────────────────────────────────
    mov  r19, r17
    eor  r19, r18         ; r19 = D

    ; ── Compute X = A'B = (~A) AND B ─────────────────────────
    mov  r20, r17
    com  r20              ; r20 = ~A  (complement)
    and  r20, r18         ; r20 = (~A) AND B = X

    ; ── Map D → PB4, X → PB5 ─────────────────────────────────
    in   r16, PORTB
    andi r16, 0b11001111  ; Clear PB4 and PB5

    sbrc r19, 0           ; Skip next if bit0 of D is clear
    ori  r16, 0b00010000  ; Set PB4

    sbrc r20, 0           ; Skip next if bit0 of X is clear
    ori  r16, 0b00100000  ; Set PB5

    out  PORTB, r16       ; Drive output LEDs
    rjmp main             ; Infinite loop
