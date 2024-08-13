
.include "swis.hdr"
.include "printmacros.hdr"

.section .init.rmf, "a"

.word     0               // offset to code    start code
.word     init + (1<<30)  // offset to code    initialisation code
.word     final           // offset to code    finalisation code
.word     0               // offset to code    service call handler
.word     title           // offset to string  title string
.word     help            // offset to string  help string
.word     0               // offset to table   help and command keyword table
.word     0               // number            SWI chunk base number
.word     0               // offset to code    SWI handler code
.word     0               // offset to table   SWI decoding table
.word     0               // offset to code    SWI decoding code
.word     0               // offset to code    Messages filename
.word     modflags        // offset to table   Module features

modflags:
.word     (0<<0) | (1<<4)

title:
.asciz "ModuleWithInit"
help:
.ascii "ModuleWithInit"
.byte 9
.asciz "1.00 (11 Aug 2024) A test of module init/final code"

.balign 4

init:
        STP     x29, x30, [sp, #-16]!
        PrintLine "Module initialising"
        PrintMessage "Environment string: "
        PrintString x0
        PrintLine ""
        LDP     x29, x30, [sp], #16
        RET


final:
        STP     x29, x30, [sp, #-16]!
        PrintLine "Module finalising"
        LDP     x29, x30, [sp], #16
        RET
