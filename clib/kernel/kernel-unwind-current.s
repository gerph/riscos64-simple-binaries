.include "asm/macros.hdr"

.text

.global _kernel_unwind_current

// Fill in the unwind block with the current status
// => x0-> unwind block
// <= x0-> unwind block, updated with current state
//          +0 = fp (eg for _kernel_unwind)
//          +4 = sp (at the time of the call)
//          +12 = lr (where we were called from, eg what called _kernel_unwind)
//          +16 = pc (where we were when we were called, eg in _kernel_unwind)
    FUNC    "_kernel_unwind_current"
    STR     x29, [x0, #0]
    MOV     x1, sp
    STR     x1, [x0, #8]
    LDR     x1, [x30, #8]
    STP     x1, x30, [x0, #16]
    RET
