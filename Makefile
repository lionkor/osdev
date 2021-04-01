ASM=nasm
CC=i686-elf-gcc
STRIP=objcopy
OBJCONV=objconv
ASMFLAGS = -f elf32 -i src -w+all -i src/kernel
CFLAGS = -Wall -Wextra -ffreestanding -g -Isrc/libc -std=gnu17
STRIPFLAGS = -R .comment -R .gnu.version -R .note -R .eh_frame -R .eh_frame_hdr -R .note.gnu.property
LDFLAGS = -T src/linker.ld -ffreestanding -O2 -nostdlib -lgcc
OBJCONVFLAGS = -fnasm
KERNEL_ELF = kernel.elf
KERNEL_OBJS = \
	$(patsubst %.c,%.c.o,$(wildcard src/kernel/*.c)) \
	$(patsubst %.c,%.c.o,$(wildcard src/kernel/*/*.c)) \
	$(patsubst %.c,%.c.o,$(wildcard src/kernel/*/*/*.c)) \

LIBC_OBJS = \
	$(patsubst %.c,%.c.o,$(wildcard src/libc/*.c)) \
	$(patsubst %.c,%.c.o,$(wildcard src/libc/*/*.c)) \
	$(patsubst %.c,%.c.o,$(wildcard src/libc/*/*/*.c)) \

.PHONY: all

all: libc.a os.iso

libc.a: $(LIBC_OBJS)
	ar rcs -o $@ $^

os.iso: os.bin
	mkdir -p isodir/boot/grub
	cp $< isodir/boot/os.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o os.iso isodir

os.bin: $(KERNEL_ELF)
	cp $< $@
	./check-multiboot.sh $@

$(KERNEL_ELF): src/kernel/kernel_entry.s.o $(KERNEL_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lc -L.

clean:
	@rm -vf *.bin *.c.s *.o src/*.c.s os.img src/*.o src/*/*.o src/*/*/*.o *.elf *.img *.iso

%.c.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

%.s.o: %.s
	$(ASM) $(ASMFLAGS) $^ -o $@

run: os.iso
	- qemu-system-i386 -kernel os.bin --enable-kvm &

debug: os.iso
	- qemu-system-i386 -kernel os.bin -s -S --enable-kvm &
	- gdb -x gdbcommands.gdb

