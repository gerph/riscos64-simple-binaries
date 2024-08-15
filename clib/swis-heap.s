.text

.global __os_heap


// =>   R0 = heap operation
//      R1 = heap base
//      R2 = pointer to block (or 0 if none)
//      R3 = size of block
//      R4 = pointer to where to store R2 on return (or NULL to ignore)
// <=   R0 = pointer to error, or NULL if ok
__os_heap:
    STP     x29, x30, [sp, #-16]!
    MOV     x10, #0x1D                  // OS_Heap
    MOVK    x10, #0x2, LSL 16           // X variant
    SVC     #0
    BVS     __os_heap_fail
    MOV     x0, #0
    CMP     x4, #0
    BEQ     __os_heap_done
    STR     x2, [x4]
__os_heap_done:
__os_heap_fail:
    LDP     x29, x30, [sp], #16
    RET
