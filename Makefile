ASM=nasm
LD=ld
CC=gcc
CXX=g++
STRIP=objcopy
OBJCONV=objconv
ASMFLAGS = -f bin -i src -w+all -i src/boot
ASMFLAGS_ELF = -f elf -i src -w+all -i src/boot
CFLAGS = -c -Wall -Wextra -O0 -ffreestanding -m32 -fno-pie
STRIPFLAGS = -R .comment -R .gnu.version -R .note -R .eh_frame -R .eh_frame_hdr -R .note.gnu.property
LDFLAGS = -Ttext 0x1000 --oformat binary -m elf_i386
OBJCONVFLAGS = -fnasm
BOOT_SECT_BIN = boot_sect.bin
BOOT_SECT_OBJS = $(patsubst %.s,%.s.o,$(wildcard src/boot/*.s))
KERNEL_BIN = kernel.bin
KERNEL_OBJS = \
	$(patsubst %.c,%.c.o,$(wildcard src/kernel/*.c)) \
	$(patsubst %.c,%.c.o,$(wildcard src/kernel/*/*.c)) \
	$(patsubst %.c,%.c.o,$(wildcard src/kernel/*/*/*.c)) \

os.img: $(BOOT_SECT_BIN) $(KERNEL_BIN)
	cat $^ > $@

$(BOOT_SECT_BIN): src/boot/boot_sect.s
	$(ASM) $(ASMFLAGS) $^ -o $@

$(KERNEL_BIN): src/kernel/kernel_entry.s.o $(KERNEL_OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

clean:
	@rm -vf *.bin *.c.s *.o src/*.c.s os.img
	@rm -vf src/*.o src/*/*.o src/*/*/*.o

src/kernel/kernel_entry.s.o: src/kernel/kernel_entry.s
	$(ASM) $(ASMFLAGS_ELF) $^ -o $@

%.c.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

%.s.o: %.s
	$(ASM) $(ASMFLAGS) $^ -o $@

run: os.img
	- qemu-system-i386 -drive format=raw,file=$<

