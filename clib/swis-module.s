.text

.global __os_module


// =>   R0 = module operation
//      R1 = pointer to block (or 0 if none)
//      R2 = size of block
//      R3 = pointer to where to store R2 on return (or NULL to ignore)
// <=   R0 = pointer to error, or NULL if ok
__os_module:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    MOV     x4, x3
    MOV     x3, x2
    MOV     x2, x1
    MOV     x10, #0x1E                  // OS_Module
    SVC     #0
    BVS     __os_module_fail

    MOV     x0, #0
    CMP     x4, #0
    BEQ     __os_module_done
    STR     x2, [x4]
__os_module_done:
__os_module_fail:
    LDP     x29, x30, [sp], #16
    RET
