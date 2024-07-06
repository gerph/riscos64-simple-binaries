# Makefile for building bin for aarch64

DIS = ~/projects/RO/pyromaniac/utils/riscos-dumpi --arm64
CROSS_ROOT = ${shell echo $$CROSS_ROOT}

DEFAULT_GOAL = mytest,ff8

all: ${DEFAULT_GOAL}

shell: dockcross-linux-arm64
	./dockcross-linux-arm64 bash

dockcross-linux-arm64:
	docker run --rm dockcross/linux-arm64:20240529-0dade71 > dockcross-linux-arm64
	chmod +x dockcross-linux-arm64

clean:
	-rm -f *.o *.bin *,ff8

ifeq (${CROSS_ROOT},)
# If we're outside the docker container, re-run ourselves inside the container
ifneq ($(filter-out all shell dockcross-linux-arm64 clean,${MAKECMDGOALS}),)
# The command wasn't one of our invocation commands above
${MAKECMDGOALS}:
	./dockcross-linux-arm64 make ${MAKECMDGOALS}
else
${DEFAULT_GOAL}:
		./dockcross-linux-arm64 make ${DEFAULT_GOAL}
endif

else

%.o: %.c
	aarch64-unknown-linux-gnu-gcc -c -o $@ $? -nostdlib -ffreestanding

%.bin: %.o | start.o swis.o
	aarch64-unknown-linux-gnu-ld start.o swis.o $? -T link.lnk -o $@

%,ff8: %.bin
	aarch64-unknown-linux-gnu-objcopy -O binary -j .text $? $@

#	otool $? -t -X | \
#        cut -c 18- | \
#        perl -ne 'for my $$x (split) { next if (!$$x); my $$v = reverse(pack("H8", $$x)) ; print $$v; }' > $@

%.dis: %.bin
	${DIS} $? > $@
	cat $@

start.o: start.s
	aarch64-unknown-linux-gnu-gcc -c -o $@ $? -nostdlib -ffreestanding

endif