# Makefile for building bin for aarch64
#
# Code compiles with:
#
#	__riscos
#	__riscos64
#   __aarch64__
#
# Norcroft defines not set:
#	__acorn
#	__arm

TARGET ?= hello_world

USE_FUNC_SIGNATURE ?= 1

CROSS_ROOT = ${shell echo $$CROSS_ROOT}

ALL_TARGETS = hello_world \
				cog \
				crash \
				hello_world_printf

CLIBDIR = clib


# Remove the flags that might make code think it's compiling for linux system.
CFLAGS = -U__linux -U__linux__ -U__unix__ -U__unix -Ulinux -Uunix -U__gnu_linux__

# Add the definitions to indicate that we're compiling for RISC OS
CFLAGS += -D__riscos -D__riscos64

# Allow us to build without assuming the standard library is present
CFLAGS += -nostdlib -ffreestanding -march=armv8-a
#CFLAGS += -nostdlib -ffreestanding -march=armv8-a+nofp

# Add the exports directory to those things we'll build with
CFLAGS += -I${CLIBDIR}/riscos_headers/C -I${CLIBDIR}/riscos_headers/Lib/ -I${CLIBDIR}/riscos_headers/Lib/CLib/

# Options to allow function signatures to appear RISC OS-like
ifeq (${USE_FUNC_SIGNATURE},1)
CFLAGS += -fpatchable-function-entry=20,20
endif

# Optimisation options
CFLAGS += -O1

# Options for this build
CFLAGS +=

# Assembler flags
AFLAGS = -march=armv8-a

# Flags for the linker
LDFLAGS = -T link.lnk -e _aif64_entry

targetted:
	make ${TARGET},ff8 TARGET=${TARGET}

all:
	for i in ${ALL_TARGETS} ; do make $$i,ff8 TARGET=$$i || exit $$? ; done

shell: dockcross-linux-arm64
	./dockcross-linux-arm64 bash

dockcross-linux-arm64:
	docker run --rm dockcross/linux-arm64:latest > dockcross-linux-arm64
	chmod +x dockcross-linux-arm64

clean:
	-rm -f *.o *.a *.bin *,ff8 *.map
	cd clib && make clean

ifeq (${CROSS_ROOT},)
# If we're outside the docker container, re-run ourselves inside the container
ifneq ($(filter-out all shell dockcross-linux-arm64 clean,${MAKECMDGOALS}),)
# The command wasn't one of our invocation commands above
.PHONY: ${MAKECMDGOALS}
${MAKECMDGOALS}: dockcross-linux-arm64 clib/libcrt.a
	./dockcross-linux-arm64 make ${MAKECMDGOALS} TARGET=${TARGET}
else
.PHONY: ${DEFAULT_GOAL}
${DEFAULT_GOAL}: dockcross-linux-arm64 clib/libcrt.a
	./dockcross-linux-arm64 make TARGET=${TARGET}
endif

${CLIBDIR}/libcrt.a:
	cd ${CLIBDIR}; make

else


CRT_OBJS = 	${CLIBDIR}/libcrt.a

CC = aarch64-unknown-linux-gnu-gcc
AS = aarch64-unknown-linux-gnu-as
LD = aarch64-unknown-linux-gnu-ld
OBJCOPY = aarch64-unknown-linux-gnu-objcopy

OBJS =	${TARGET}.o

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $?

%.o: %.s
	${AS} ${AFLAGS} -o $@ $?

${TARGET}.bin: link.lnk ${OBJS} ${CRT_OBJS}
	${LD} ${OBJS} ${CRT_OBJS} ${LDFLAGS} -o $@

${TARGET}.map: link.lnk ${OBJS} ${CRT_OBJS}
	${LD} ${OBJS} ${CRT_OBJS} ${LDFLAGS} -Map $@ -o /dev/null

ifeq (${USE_FUNC_SIGNATURE},1)
${TARGET},ff8: ${TARGET}.bin ${TARGET}.map
	${OBJCOPY} -O binary -j .text ${TARGET}.bin $@
	python riscos_symbols.py ${TARGET}.map ${TARGET},ff8
else
${TARGET},ff8: ${TARGET}.bin
	${OBJCOPY} -O binary -j .text ${TARGET}.bin $@
endif

endif
