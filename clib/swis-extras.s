.text

.global draw_fill
.global colourtrans_setgcol
.global os_screenmode
.global os_setcolour
.global os_byte_out1


draw_fill:
    STP     x29, x30, [sp, #-16]!
    MOV     x10, #0x702                 // Draw_Fill
    MOVK    x10, #0x4, LSL 16           // Draw_Fill
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

// OS_Byte with simple semantics
// int os_byte_out1(r0, r1, r2) => r1 value on return
os_byte_out1:
    STP     x29, x30, [sp, #-16]!
    MOV     x10, #0x6                   // OS_Byte
    SVC     #0
    MOV     x0, x1
    LDP     x29, x30, [sp], #16
    RET
