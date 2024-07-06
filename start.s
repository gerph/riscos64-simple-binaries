.text

.balign 4
_start:
// This is an AIF-like header. We wouldn't actually use this in real cases,
// as it would break on non-AArch64 systems. It's arguable that we shouldn't
// care and shouldn't use an absolute file of type FF8. Use a different type
// and avoid the whole problem.
        B       _setup_env
        NOP
        NOP
        NOP
        NOP                     // Was OS_Exit
.word   0                       // read only size (FIXME?)
.word   0                       // read write size (FIXME?)
.word   0                       // debug size
.word   0                       // zero init size
.word   0                       // debug type
.word   _start                  // execution address
.word   0                       // workspace size
.word   64                      // address mode
.word   0                       // data base address
.word   0                       // reserved
.word   0                       // reserved

_setup_env:
// Set up the stack pointer
        MOV     x10, #0x10      // OS_GetEnv
        SVC     #0

        MOV     sp, x1          // Set the stack pointer to our memory limit (maybe this should be implicit now?)
        BL      start

        MOV     x10, #0x11      // OS_Exit
        MOV     x2, x0
        ADR     x0, return_error
        LDR     x1, abex
        SVC     #0

abex:
.word   0x58454241

return_error:
.word   0x0                     // error number (FIXME)
.string "Bad exit code"
.align  4
