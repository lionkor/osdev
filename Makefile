ASM=nasm
LD=ld
CC=gcc
STRIP=objcopy
OBJCONV=objconv
ASMFLAGS = -f bin -i src -Ox -w+all
CFLAGS = -c -Wall -Wextra -nostdlib -m32 -Os -ffunction-sections -fdata-sections -fno-unwind-tables -fno-asynchronous-unwind-tables
STRIPFLAGS = -R .comment -R .gnu.version -R .note -R .eh_frame -R .eh_frame_hdr -R .note.gnu.property
OBJCONVFLAGS = -fnasm

.PHONY: clean

clean: 
	rm -vf *.bin *.c.s *.o

%.c.s: src/%.c
	$(CC) $(CFLAGS) $^ -o $*.o
	$(STRIP) $(STRIPFLAGS) $*.o # removes only sections we don't want, keep debug symbols
	$(OBJCONV) $(OBJCONVFLAGS) $*.o $@ >/dev/null
	rm $*.o
	sed -i 's|st(0)|st0  |g' $@
	sed -i 's|noexecute|         |g' $@
	sed -i 's|execute|       |g' $@
	sed -i 's|: function||g' $@
	sed -i 's|?_|L_|g' $@
	sed -i -n '/SECTION .eh_frame/q;p' $@
	sed -i 's|;.*||g' $@
	sed -i 's/^M//g' $@

%.c.bin: %.c.s
	$(ASM) $(ASMFLAGS) $^ -o $@

%.bin: src/%.s
	$(ASM) $(ASMFLAGS) $^ -o $@

run_%: %.bin
	qemu-system-x86_64 $^ -nographic
