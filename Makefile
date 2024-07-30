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

DIS = ~/projects/RO/pyromaniac/utils/riscos-dumpi --arm64
CROSS_ROOT = ${shell echo $$CROSS_ROOT}

ALL_TARGETS = hello_world \
				cog \



# Remove the flags that might make code think it's compiling for linux system.
CFLAGS = -U__linux -U__linux__ -U__unix__ -U__unix -Ulinux -Uunix -U__gnu_linux__

# Add the definitions to indicate that we're compiling for RISC OS
CFLAGS += -D__riscos -D__riscos64

# Allow us to build without assuming the standard library is present
CFLAGS += -nostdlib -ffreestanding -march=armv8-a
#CFLAGS += -nostdlib -ffreestanding -march=armv8-a+nofp

# Add the exports directory to those things we'll build with
CFLAGS += -Iriscos_headers/C/ -Iriscos_headers/Lib/

# Options to allow function signatures to appear RISC OS-like
ifeq (${USE_FUNC_SIGNATURE},1)
CFLAGS += -fpatchable-function-entry=20,20
endif

# Optimisation options
CFLAGS += -O1

# How much static heap we'll allocate
CFLAGS += -DHEAP_SIZE=1024

# Options for this build
CFLAGS += 

targetted: local_headers
	make ${TARGET},ff8 TARGET=${TARGET}

all: local_headers
	for i in ${ALL_TARGETS} ; do make $$i,ff8 TARGET=$$i || exit $$? ; done

local_headers:
	mkdir -p riscos_headers/C/
ifeq (${CEXPORT_DIR},)
	echo No local headers defined in CEXPORT_DIR
else
	for hdr in ${CEXPORT_DIR}/h/* ; do cp "$$hdr" "riscos_headers/C/$$(basename "$$hdr").h" ; done
	#for hdrdir in ${LIB_DIR}/* ; do mkdir -p "riscos_headers/Lib/$$(basename "$$hdrdir")" ; for hdr in "$$hdrdir/h"/* ; do cp "$$hdr" "riscos_headers/Lib/$$(basename "$$hdrdir")/$$(basename "$$hdr").h" ; done ; done
endif

shell: dockcross-linux-arm64
	./dockcross-linux-arm64 bash

dockcross-linux-arm64:
	docker run --rm dockcross/linux-arm64:latest > dockcross-linux-arm64
	chmod +x dockcross-linux-arm64

clean:
	-rm -f *.o *.bin *,ff8 *.map

ifeq (${CROSS_ROOT},)
# If we're outside the docker container, re-run ourselves inside the container
ifneq ($(filter-out all shell dockcross-linux-arm64 clean,${MAKECMDGOALS}),)
# The command wasn't one of our invocation commands above
.PHONY: ${MAKECMDGOALS}
${MAKECMDGOALS}: dockcross-linux-arm64
	./dockcross-linux-arm64 make ${MAKECMDGOALS} TARGET=${TARGET}
else
.PHONY: ${DEFAULT_GOAL}
${DEFAULT_GOAL}: dockcross-linux-arm64
	./dockcross-linux-arm64 make TARGET=${TARGET}
endif

else


CRT_OBJS = 	\
			clib.o \
			clib-main.o \
			clib-malloc.o \
			clib-kernel.o \
			clib-strtol.o \
			clib-strtod.o \
			clib-strdup.o \

OBJS =	${CRT_OBJS} \
		${TARGET}.o

%.o: %.c
	aarch64-unknown-linux-gnu-gcc ${CFLAGS} -c -o $@ $?

${TARGET}.bin: start.o swis.o link.lnk ${OBJS}
	aarch64-unknown-linux-gnu-ld start.o swis.o ${OBJS} -T link.lnk -o $@

${TARGET}.map: start.o swis.o link.lnk ${OBJS}
	aarch64-unknown-linux-gnu-ld start.o swis.o ${OBJS} -T link.lnk -Map $@ -o /dev/null

ifeq (${USE_FUNC_SIGNATURE},1)
${TARGET},ff8: ${TARGET}.bin ${TARGET}.map
	aarch64-unknown-linux-gnu-objcopy -O binary -j .text ${TARGET}.bin $@
	python riscos_symbols.py ${TARGET}.map ${TARGET},ff8
else
${TARGET},ff8: ${TARGET}.bin
	aarch64-unknown-linux-gnu-objcopy -O binary -j .text ${TARGET}.bin $@
endif

start.o: start.s
	aarch64-unknown-linux-gnu-gcc ${CFLAGS} -c -o $@ $?

endif
