.include "swis.hdr"
.include "printmacros.hdr"

.text

.global _entry

_entry:
        STP     x29, x30, [sp, #-16]!
        PrintLine "Hello world"
        PrintMessage "Environment string: "
        PrintString x1
        PrintLine ""
        MOV     x0, #0      // no error return
        LDP     x29, x30, [sp], #16
        RET

.bss
.skip 20
