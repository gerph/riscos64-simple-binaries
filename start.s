.text

.global _start
.global exit


.balign 4
_start:
// Set up the stack pointer
        MOV     x10, #0x10      // OS_GetEnv
        SVC     #0

        MOV     sp, x1          // Set the stack pointer to our memory limit (maybe this should be implicit now?)
        BL      start

exit:
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
