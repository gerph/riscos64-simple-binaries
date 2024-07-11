# Simple RISC OS 64 binaries

This repository contains some build tools for RISC OS 64bit binaries.

## Usage

To build everything on a POSIX system you will require Docker, and should be able to type:

    make

to build the binaries.

The binaries will be produced as `,ff8` suffixed files.


## AIF Format

The 64bit AIF format has been defined as follows:

| Offset | Value     | Instructions | Meaning |
| ------ | --------- | ------------ | ------- |
| &000   | &e1a00000 | ARM32: `NOP`             | ARM32 decompression |
| &004   | &e1a00000 | ARM32: `NOP`             | ARM32 reloc |
| &008   | &e1a00000 | ARM32: `NOP`             | ARM32 zero init |
| &00C   | &eb00000b | ARM32: `BL      entry`   | ARM32 image entry |
| &010   | &ef000011 | ARM32: `SWI     OS_Exit` | explicit OS_Exit |
| &014   | variable  | code + static data size  | read only size |
| &018   | variable  | R/W data size| read write size |
| &01C   | &0        | - | debug size |
| &020   | &0        | - | zero init size |
| &024   | &0        | - | debug type |
| &028   | &8000     | - | linked base address |
| &02C   | &0        | - | workspace size (obsolete) |
| &030   | &40       | - | address mode |
| &034   | &0        | - | data base address |
| &038   | &0        | - | reserved |
| &03c   | &0        | - | reserved |
| &040   | &e28f0000 | ARM32: `entry: ADR     r0, error_block`    | ARM32 error report |
| &044   | &ef00002b | ARM32: `SWI     OS_GenerateError`          |  |
| &048   | &0        | ARM32: `error_block: DCD     0` |  |
| &04c   | string    | ARM32: `= "AArch64 binaries cannot be run on 32bit RISC OS", 0` |  |
| &07c   | &0        | ARM32: `DCD     0` |  |
| ... |
| &100   | ARM64: start ... | AArch64 entry point |
