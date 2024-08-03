.section .init.aif

.global _start
.global _Exit


.balign 4
_aif64_entry:
        NOP                     // Relocation code (not currently used)
        BL      _zeroinit       // Zero initialisation
        BL      _start
        MOV     x10, #0x11      // OS_Exit
        SVC     #0

_zeroinit:
        SUB     x0, lr, #0x100 + 0x8    // Start of the application space
        LDR     w3, [x0, #0x14] // code size
        LDR     w4, [x0, #0x18] // data size
        ADD     x1, x0, x3
        ADD     x1, x1, x4
        LDR     w4, [x0, #0x20] // zero init size
        MOV     x5, #0
        MOV     x6, #0

        CMP     x4, #128
        BLO     _zeroinit_fastdone
_zeroinit_fastloop:
        STP     x5, x6, [x1], #16
        STP     x5, x6, [x1], #16
        STP     x5, x6, [x1], #16
        STP     x5, x6, [x1], #16
        STP     x5, x6, [x1], #16
        STP     x5, x6, [x1], #16
        STP     x5, x6, [x1], #16
        STP     x5, x6, [x1], #16
        SUB     x4, x4, #128
        CMP     x4, #128
        BHS     _zeroinit_fastloop
_zeroinit_fastdone:
        CMP     x4, #4
        BLO     _zeroinit_slowdone
_zeroinit_slowloop:
        STR     w5, [x1], #4
        SUB     x4, x4, #4
        CMP     x4, #4
        BHS     _zeroinit_slowloop

_zeroinit_slowdone:
        RET

_start:
// Set up the stack pointer
        MOV     x10, #0x10      // OS_GetEnv
        SVC     #0

        MOV     fp, #0          // Clear the frame pointer
        MOV     sp, x1          // Set the stack pointer to our memory limit (maybe this should be implicit now?)

        MOV     x3, x1          // memory limit
        SUB     x1, lr, #0x100 + 0xC    // Start of the application space

// x0-> start string
// x1-> start of application
// x2-> end of application
// x3-> end of memory
        LDR     w2, [x1, #0x14] // code size
        LDR     w4, [x1, #0x18] // data size
        ADD     x2, x1, x2
        ADD     x2, x2, x4

        BL      __main

_Exit:
        MOV     x2, x0
        ADR     x0, return_error
        LDR     x1, abex
        MOV     x10, #0x11      // OS_Exit
        SVC     #0

abex:
.word   0x58454241

return_error:
.word   0x0                     // error number (FIXME)
.string "Bad exit code"
.align  4
