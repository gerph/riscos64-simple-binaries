.include "asm/macros.hdr"
.include "asm/swis.hdr"

.text

.global _Exit


        FUNC    "_Exit"
        MOV     x19, x0
        BL      _env_restore    // restore caller environment
        MOV     x2, x19
        ADR     x0, return_error
        LDR     x1, abex
        MOV     x10, #OS_Exit
        SVC     #0

abex:
.word   0x58454241

return_error:
.word   0x0                     // error number (FIXME)
.string "Bad exit code"
.align  4
