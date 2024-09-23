.text

.global __os_writec
.global __os_readc
.global __os_word
.global __os_inkey
.global __os_write0
.global __os_writen
.global __os_newline
.global __os_readescapestate
.global __os_generateerror
.global __os_file2
.global __os_file3
.global __os_fscontrol2
.global __os_fscontrol3

.global _kernel_osfile


__os_writec:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    MOV     x10, #0                     // OS_WriteC
    ORR     x10, x10, #0x20000
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

__os_readc:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    MOV     x10, #4                     // OS_ReadC
    ORR     x10, x10, #0x20000
    SVC     #0
    CSINV   x0, x0, xzr, VS
    LDP     x29, x30, [sp], #16
    RET

__os_word:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    STRB    w1, [x2]
    MOV     x1, x2
    MOV     x10, #7                     // OS_Word
    ORR     x10, x10, #0x20000
    SVC     #0
    CSEL    x0, x0, xzr, VS
    LDP     x29, x30, [sp], #16
    RET

__os_inkey:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    AND     x1, x0, #255
    LSR     x2, x0, #8
    MOV     x0, #0x81                   // INKEY
    MOV     x10, #0x6                   // OS_Byte
    ORR     x10, x10, #0x20000
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
    ORR     x10, x10, #0x20000
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

__os_writen:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    MOV     x10, #0x46                  // OS_WriteN
    ORR     x10, x10, #0x20000
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

__os_newline:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    MOV     x10, #0x3                   // OS_NewLine
    ORR     x10, x10, #0x20000
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

__os_readescapestate:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    MOV     x10, #0x2C                  // OS_ReadEscapeState
    ORR     x10, x10, #0x20000
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

__os_file2:
__os_file3:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    MOV     x10, #0x9                   // OS_File
    ORR     x10, x10, #0x20000
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

/* => x0 = op
      x1-> filename
      x2-> buffer for x2-x5 (in and out)
   <= r0 = r0 on return; or -1 if error.
 */
_kernel_osfile:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp

    MOV     x6, x3

    CMP     x6, #0
    BEQ     _kosfile_skip_load

_kosfile_skip_load:
    LDP     w4, w5, [x6, #8]
    LDP     w2, w3, [x6]

    MOV     x10, #0x9                   // OS_File
    ORR     x10, x10, #0x20000
    SVC     #0

    CMP     x6, #0
    BEQ     _kosfile_skip_store

    STP     w4, w5, [x6, #8]
    STP     w2, w3, [x6]

_kosfile_skip_store:
    MOV     x6, #-2
    CSEL    x0, x0, x6, VS              // return -2 if error, or x0 if not

    LDP     x29, x30, [sp], #16
    RET

__os_fscontrol2:
__os_fscontrol3:
    STP     x29, x30, [sp, #-16]!
    MOV     x29, sp
    MOV     x10, #0x29                  // OS_FSControl
    ORR     x10, x10, #0x20000
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

