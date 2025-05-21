.include "swis.hdr"

.text

.global _entry

_entry:
        STP     x29, x30, [sp, #-16]!
        MOV     x29, sp
        BL      __RelocCode
        MOV     x3, x1

        MOV     x10, #OS_WriteS
        SVC     #0
.asciz "Hello "
.balign 4

        LDRB    w1, [x3]
        ADR     x2, message_world
        CMP     w1, #0
        CSEL    x0, x2, x3, eq

        MOV     x10, #OS_Write0
        SVC     #0

        MOV     x10, #OS_NewLine
        SVC     #0

        MOV     x0, #0      // no error return
        LDP     x29, x30, [sp], #16
        RET

message_world:
.asciz "world"

