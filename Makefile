ASM=nasm
LD=ld
CC=gcc
CXX=g++
STRIP=objcopy
OBJCONV=objconv
ASMFLAGS = -f bin -i src -Ox -w+all -i src/boot
CFLAGS = -c -Wall -Wextra -O0 -ffreestanding
STRIPFLAGS = -R .comment -R .gnu.version -R .note -R .eh_frame -R .eh_frame_hdr -R .note.gnu.property
LDFLAGS = -O1 -Ttext 0x0 --oformat binary
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

$(KERNEL_BIN): $(KERNEL_OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

clean: 
	@rm -vf *.bin *.c.s *.o src/*.c.s os.img
	@rm -vf src/*.o src/*/*.o src/*/*/*.o

%.c.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

%.s.o: %.s
	$(ASM) $(ASMFLAGS) $^ -o $@

run: os.img
	- qemu-system-x86_64 -drive format=raw,file=$< -nographic
