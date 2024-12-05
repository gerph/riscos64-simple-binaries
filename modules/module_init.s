.include "Asm/macros.hdr"

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
.word	0 + (1<<2) + (1<<4) // 32bit NOT supported + zero-init present + AArch64
.word   _zinit_size         // Size of our Zero initialised area

title:
.asciz "ModuleWithInit"
help:
.ascii "ModuleWithInit"
.byte 9
.asciz "1.00 (11 Aug 2024) A test of module init/final code"

.balign 4

        FUNC    "init"
        STP     x29, x30, [sp, #-16]!
        PrintLine "Module initialising"
        PrintMessage "Environment string: "
        PrintString x0
        PrintLine ""
        MOV     x0, #0      // no error return
        LDP     x29, x30, [sp], #16
        RET


        FUNC    "final"
        STP     x29, x30, [sp, #-16]!
        PrintLine "Module finalising"
        MOV     x0, #0      // no error return
        LDP     x29, x30, [sp], #16
        RET
