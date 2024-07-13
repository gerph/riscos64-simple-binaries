.text

.global os_writec
.global draw_fill
.global os_readc
.global colourtrans_setgcol
.global os_screenmode
.global os_setcolour
.global os_inkey
.global os_write0
.global os_newline
.global os_byte_out1


os_writec:
    STP     x29, x30, [sp, #-16]!
    MOV     x10, #0                     // OS_WriteC
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

draw_fill:
    STP     x29, x30, [sp, #-16]!
    MOV     x10, #0x702                 // Draw_Fill
    MOVK    x10, #0x4, LSL 16           // Draw_Fill
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

os_readc:
    STP     x29, x30, [sp, #-16]!
    MOV     x10, #4                     // OS_ReadC
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

os_screenmode:
    STP     x29, x30, [sp, #-16]!
    MOV     x10, #0x65                  // OS_ScreenMode
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

colourtrans_setgcol:
    STP     x29, x30, [sp, #-16]!
    MOV     x3, x1
    MOV     x4, x2
    MOV     x10, #0x743                 // ColourTrans_SetGCOL
    MOVK    x10, #0x4, LSL 16           // ColourTrans_SetGCOL
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

os_setcolour:
    STP     x29, x30, [sp, #-16]!
    MOV     x10, #0x61                  // OS_SetColour
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

os_inkey:
    STP     x29, x30, [sp, #-16]!
    AND     x1, x0, #255
    LSR     x2, x0, #8
    MOV     x0, #0x81                   // INKEY
    MOV     x10, #0x6                   // OS_Byte
    SVC     #0
                                        // Returns R1 = character read
                                        //         R2 = 0 =>char was read, 27=>escape, 255=>nothing read
// We are going to return -1 for nothing read, and -2 for escape
    CMP     x2, #27
    BEQ     os_inkey_escape
    CMP     x2, #255
    CSINV   x0, x1, xzr, NE             // if x2!=255 x0=x1 else x0=-1
os_inkey_exit:
    LDP     x29, x30, [sp], #16
    RET

os_inkey_escape:
    MOV     x0, #-2
    B       os_inkey_exit

os_write0:
    STP     x29, x30, [sp, #-16]!
    MOV     x10, #0x2                   // OS_Write0
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

os_newline:
    STP     x29, x30, [sp, #-16]!
    MOV     x10, #0x3                   // OS_NewLine
    SVC     #0
    LDP     x29, x30, [sp], #16
    RET

// OS_Byte with simple semantics
// int os_byte_out1(r0, r1, r2) => r1 value on return
os_byte_out1:
    STP     x29, x30, [sp, #-16]!
    MOV     x10, #0x6                   // OS_Byte
    SVC     #0
    MOV     x0, x1
    LDP     x29, x30, [sp], #16
    RET
