#ifndef ENVNUMBERS_H
#define ENVNUMBERS_H

enum envnumbers_e {
    MemoryLimit             = 0,     // R2 ignored
    UndefinedHandler        = 1,     //  "    "
    PrefetchAbortHandler    = 2,     //  "    "
    DataAbortHandler        = 3,     //  "    "
    AddressExceptionHandler = 4,     //  "    "
    OtherExceptionHandler   = 5,     // for FPU exception etc. expansion
    ErrorHandler            = 6,     // R3 is error buffer pointer
    CallBackHandler         = 7,     // R3 is register buffer ptr
    BreakPointHandler       = 8,     // R3 is register buffer ptr
    EscapeHandler           = 9,
    EventHandler            = 10,
    ExitHandler             = 11,
    UnusedSWIHandler        = 12,
    ExceptionDumpArea       = 13,
    ApplicationSpaceSize    = 14,
    CAOPointer              = 15,
    UpCallHandler           = 16,
};

#endif
