# Makefile for building CLib library for aarch64
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

CROSS_ROOT = ${shell echo $$CROSS_ROOT}

ALL_TARGETS = libcrt.a

DEFAULT_GOAL = libcrt.a


targetted: export_headers
	make ${DEFAULT_GOAL}

.PHONY: export

export: targetted
	rm -rf export
	mkdir export
	cp -R libcrt.a export/
	cp -R riscos_headers/* export/
	mv export/Lib/CLib/* export/
	rmdir export/Lib/CLib
	rm export/_marker
	cp -R bin export/

# NOTE: Not used yet
all: export_headers
	for i in ${ALL_TARGETS} ; do make $$i,ff8 TARGET=$$i || exit $$? ; done

export_headers: local_headers \
				riscos_headers/Lib/CLib/swis.h \
				riscos_headers/Lib/CLib/kernel.h \
				riscos_headers/Lib/CLib/swi_numbers.h \
				riscos_headers/Lib/CLib/swis_os.h \
				riscos_headers/Lib/CLib/_heap_implementation.h

riscos_headers/Lib/CLib/%.h: %.h | local_headers
	cp $? $@
riscos_headers/Lib/CLib/%.h: heap/%.h | local_headers
	cp $? $@

local_headers: riscos_headers/_marker
riscos_headers/_marker:
	mkdir -p riscos_headers/C/riscos
	mkdir -p riscos_headers/Lib/CLib
ifeq (${CEXPORT_DIR},)
	echo No local headers defined in CEXPORT_DIR
else
	for hdr in ${CEXPORT_DIR}/h/* ; do cp "$$hdr" "riscos_headers/C/$$(basename "$$hdr").h" ; done
	for hdr in ${CEXPORT_DIR}/riscos/h/* ; do cp "$$hdr" "riscos_headers/C/riscos/$$(basename "$$hdr").h" ; done
	for hdrdir in ${LIB_DIR}/* ; do mkdir -p "riscos_headers/Lib/$$(basename "$$hdrdir")" ; for hdr in "$$hdrdir/h"/* ; do cp "$$hdr" "riscos_headers/Lib/$$(basename "$$hdrdir")/$$(basename "$$hdr").h" ; done ; done
	# For now, we don't want to export all the old RISC OS header files from Norcroft
	-rmdir riscos_headers/Lib/*
	rm riscos_headers/Lib/CLib/*
endif
	touch riscos_headers/_marker


shell: dockcross-linux-arm64
	./dockcross-linux-arm64 bash

dockcross-linux-arm64:
	docker run --rm dockcross/linux-arm64:latest > dockcross-linux-arm64
	chmod +x dockcross-linux-arm64

clean:
	-rm -rf *.o *.a *.bin *,ff8 *.map riscos_headers/ export/
	-rm -rf heap/*.o

ifeq (${CROSS_ROOT},)
# If we're outside the docker container, re-run ourselves inside the container
ifneq ($(filter-out all shell dockcross-linux-arm64 clean export,${MAKECMDGOALS}),)
# The command wasn't one of our invocation commands above
.PHONY: ${MAKECMDGOALS}
${MAKECMDGOALS}: dockcross-linux-arm64
	./dockcross-linux-arm64 make ${MAKECMDGOALS}
else
.PHONY: ${DEFAULT_GOAL}
${DEFAULT_GOAL}: dockcross-linux-arm64
	./dockcross-linux-arm64 make ${DEFAULT_GOAL}
endif

else
# We are inside the docker container

USE_FUNC_SIGNATURE ?= 1

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
CFLAGS += -fpatchable-function-entry=8,8
endif

# Optimisation options
CFLAGS += -O1

# Options for this build
CFLAGS += -DARCH_HAS_DIVISION

# Assembler flags
AFLAGS = -march=armv8-a


CC = aarch64-unknown-linux-gnu-gcc
AS = aarch64-unknown-linux-gnu-as
LD = aarch64-unknown-linux-gnu-ld
AR = aarch64-unknown-linux-gnu-ar
OBJCOPY = aarch64-unknown-linux-gnu-objcopy

OBJS = 	\
		assert.o \
		ctypes.o \
		errno.o \
		\
		heap/accumulator.o \
		heap/osheap.o \
		heap/o1heap.o \
		heap/o1heap-shim.o \
		heap/init.o \
		\
		io-constants.o \
		io-console.o \
		io-file-init.o \
		io-file.o \
		io-fprintf.o \
		io-printf.o \
		io-sprintf.o \
		io-vprintf.o \
		kernel-backtrace.o \
		kernel-escape.o \
		kernel-state.o \
		kernel-cli.o \
		kernel-unwind-current.o \
		kernel-unwind.o \
		kernel.o \
		longjmp.o \
		main.o \
		main-exit.o \
		module.o \
		malloc.o \
		mem.o \
		qsort.o \
		strdup.o \
		string-strcpy.o \
		string-strlen.o \
		string.o \
		strtod.o \
		strtol.o \
		strtoul.o \
		time.o \
		sysvars.o \
		sysvars-kernel.o \
		sysvars-init.o \
		version.o \
		\
		e_rem_pio2.o \
		k_rem_pio2.o \
		k_cos.o \
		s_cos.o \
		k_sin.o \
		s_sin.o \
		s_floor.o \
		s_scalbn.o \
		\
		cvt_decimal.o \
		cvt_hex.o \
		\
		swis-extras.o \
		swis-kernel.o \
		swis-module.o \
		swis-heap.o \
		swis.o \
		start.o \
		start-exit.o \

#		trunc.o \
#		fabs.o \


libcrt.a: ${OBJS}
	${AR} -rc $@ ${OBJS}

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $?

%.o: %.s
	${AS} ${AFLAGS} -o $@ $?


endif
