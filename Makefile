# Makefile for building bin for aarch64

USE_FUNC_SIGNATURE ?= 1

DIS = ~/projects/RO/pyromaniac/utils/riscos-dumpi --arm64
CROSS_ROOT = ${shell echo $$CROSS_ROOT}

DEFAULT_GOAL = hello_world,ff8 cog,ff8

CFLAGS = -nostdlib -ffreestanding

ifeq (${USE_FUNC_SIGNATURE},1)
CFLAGS += -fpatchable-function-entry=20,20
endif

all: ${DEFAULT_GOAL}

shell: dockcross-linux-arm64
	./dockcross-linux-arm64 bash

dockcross-linux-arm64:
	docker run --rm dockcross/linux-arm64:20240529-0dade71 > dockcross-linux-arm64
	chmod +x dockcross-linux-arm64

clean:
	-rm -f *.o *.bin *,ff8 *.map

ifeq (${CROSS_ROOT},)
# If we're outside the docker container, re-run ourselves inside the container
ifneq ($(filter-out all shell dockcross-linux-arm64 clean,${MAKECMDGOALS}),)
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

%.o: %.c
	aarch64-unknown-linux-gnu-gcc ${CFLAGS} -c -o $@ $?

%.bin: %.o | start.o swis.o link.lnk
	aarch64-unknown-linux-gnu-ld start.o swis.o $? -T link.lnk -o $@

%.map: %.o | start.o swis.o link.lnk
	aarch64-unknown-linux-gnu-ld start.o swis.o $? -T link.lnk -Map $@ -o /dev/null

ifeq (${USE_FUNC_SIGNATURE},1)
%,ff8: %.bin %.map
	aarch64-unknown-linux-gnu-objcopy -O binary -j .text $*.bin $@
	python riscos_symbols.py $*.map $*,ff8
else
%,ff8: %.bin
	aarch64-unknown-linux-gnu-objcopy -O binary -j .text $*.bin $@
endif

%.dis: %,ff8
	${DIS} $? > $@
	cat $@

start.o: start.s
	aarch64-unknown-linux-gnu-gcc ${CFLAGS} -c -o $@ $?

endif
