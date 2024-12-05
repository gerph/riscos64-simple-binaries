.include "asm/macros.hdr"

.text

.global _Exit


        FUNC    "_Exit"
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
