# Makefile for building bin for aarch64

DIS = ~/projects/RO/pyromaniac/utils/riscos-dumpi --arm64

all: mytest,ff8

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
