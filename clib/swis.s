.text

.global __os_writec
.global __os_readc
.global __os_inkey
.global __os_write0
.global __os_writen
.global __os_newline
.global __os_readescapestate
.global __os_generateerror



__os_writec:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    MOV     x10, #0                     // OS_WriteC
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

__os_readc:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    MOV     x10, #4                     // OS_ReadC
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

__os_inkey:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    AND     x1, x0, #255
    LSR     x2, x0, #8
    MOV     x0, #0x81                   // INKEY
    MOV     x10, #0x6                   // OS_Byte
    SVC     #0                          // Returns R1 = character read
                                        //         R2 = 0 =>char was read, 27=>escape, 255=>nothing read
// We are going to return -1 for nothing read, and -2 for escape
    CMP     x2, #27
    BEQ     __os_inkey_escape
    CMP     x2, #255
    CSINV   x0, x1, xzr, NE             // if x2!=255 x0=x1 else x0=-1
__os_inkey_exit:
    LDP     x29, x30, [sp], #16
    RET

__os_inkey_escape:
    MOV     x0, #-2
    B       __os_inkey_exit

__os_write0:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    MOV     x10, #0x2                   // OS_Write0
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

__os_writen:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    MOV     x10, #0x46                  // OS_WriteN
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

__os_newline:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    MOV     x10, #0x3                   // OS_NewLine
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

__os_readescapestate:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    MOV     x10, #0x2C                  // OS_ReadEscapeState
    SVC     #0
// We avoid flag returns from SWIs on RISC OS 64, so this returns the state in x0
    LDP     x29, x30, [sp], #16
    RET

__os_generateerror:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    MOV     x10, #0x2B                  // OS_GenerateError
    SVC     #0
    LDP     x29, x30, [sp], #16
    MOV     x0, #1                      // If OS_GenerateError returns, we jump to the exit code
    B       exit

