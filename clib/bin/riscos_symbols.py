#!/bin/env python
"""
Poke RISC OS style function names into the binary.

We use `-fpatchable-function-entry=20,20` when compiling to leave space
for a patched function name before the function. We generate a map file
that contains the names of the functions in the file.

This program will take those function names and the binary and patch
them into it.

The input can be either the output from the `ld ... --Map file.map`
switch or the output from `objdump --syms ...`. The former doesn't
include the local symbols.
"""

import sys
import struct

debug = False

map_file = sys.argv[1]
bin_file = sys.argv[2]

max_func_len = 20*4 - 4

in_memory_map = False
in_text = False

base_address = None

functions = {}

map_type = 'unknown'

# Read the symbols from the map file
with open(map_file, "r") as fh:
    for line in fh:
        line = line.rstrip()
        if map_type == 'unknown':
            if line.startswith('Archive member included to satisfy reference') or line == 'Memory Configuration':
                map_type = 'linker-map'
            elif line == 'SYMBOL TABLE:':
                map_type = 'objdump-symbols'

        elif map_type == 'linker-map':
            if line.startswith('Linker script and memory map'):
                in_memory_map = True
            elif line.startswith('OUTPUT'):
                in_memory_map = False
            elif in_memory_map:
                if line.startswith(' .text'):
                    in_text = True
                    line = '      ' + line[6:]

                elif line.startswith((' .data', ' .rodata')):
                    in_text = False

                if in_text:
                    if line.startswith('                0x'):
                        # Possibly one of our lines
                        line = line[16:]
                        addr = int(line[0:18], 16)
                        line = line[18:]
                        if line.startswith('                '):
                            # Looks good; probably the function left
                            func = line[16:]
                            if ' ' not in func and len(func) < max_func_len:
                                #print("%08x : %s" % (addr, func))
                                functions[addr] = func

                elif base_address is None:
                    # Not in text but we're in the memory map
                    if line.startswith('                0x'):
                        # This is our first address
                        line = line[16:]
                        base_address = int(line[0:18], 16)

        elif map_type == 'objdump-symbols':
            if len(line) > 20:
                # Minimum requirements
                address = line[0:16]
                flags = line[17:25]
                tail = line[25:]
                if '\t' not in tail:
                    print("Unrecognised line: '%s'" % (line,))
                    continue
                (region, tail) = tail.split('\t', 1)
                if debug:
                    print("Flags: '%s', Region: '%s', tail: '%s'" % (flags, region, tail))
                if ' ' not in tail:
                    # Entry without a symbol name
                    #print("Unrecognised line: '%s'" % (line,))
                    continue
                (size, symbol) = tail.split(' ', 1)
                try:
                    address = int(address, 16)
                    size = int(size, 16)

                    if 'F' in flags and region.startswith('.text'):
                        # This is a function symbol in the code
                        functions[address] = symbol

                    if 'g' in flags and region == '*ABS*' and 'f' not in flags:
                        if base_address is None or base_address > address:
                            base_address = address
                except ValueError:
                    # Not an address line
                    pass

# Read the binary file
with open(bin_file, "rb") as fh:
    bin_data = fh.read()

nop = 0xd503201f
nop_bytes = struct.pack('<L', nop)

# Process each of our symbols into the file
for addr, symbol in sorted(functions.items()):
    symbol_len = (len(symbol) + 4) & ~3
    space_needed = 4 + symbol_len
    symbol_start = addr - base_address - space_needed
    currently = bin_data[symbol_start:symbol_start + space_needed]
    if currently[-4:] != nop_bytes:
        # This function isn't preceded by any NOPs, so it's not possible to signature it.
        # We'll assume it's an assembler function or similar and just ignore.
        pass
    else:
        if currently == nop_bytes * int(space_needed / 4):
            if debug:
                print("Symbol '%s' can be patched at address &%08x" % (symbol, addr))
            pre = bin_data[:symbol_start]
            post = bin_data[symbol_start + space_needed:]
            try:
                patch = bytearray(symbol) + b'\0'
            except TypeError:
                patch = bytearray(symbol, 'ascii') + b'\0'
            while len(patch) & 3:
                patch += b'\0'
            patch += bytearray([symbol_len, 0,0,255])
            bin_data = pre + patch + post
        else:
            print("Warning: Failed to patch symbol name in '%s'" % (symbol,))
            if debug:
                print("  Currently: %r" % (currently,))
                print("  Need:      %r" % (nop_bytes * (space_needed / 4),))


with open(bin_file, "wb") as fh:
    fh.write(bin_data)
