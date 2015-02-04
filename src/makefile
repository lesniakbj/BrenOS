SOURCES = boot.o kernel.o
CFLAGS = -m32 -std=gnu99 -nostdlib -ffreestanding -fno-builtin -fno-stack-protector
LDFLAGS = -T link.ld -nostdlib -lgcc
ASFLAGS = -f elf32

all: $(SOURCES) link

clean:
	-rm *.o kernel.bin

link:
	i686-elf-ld $(LDFLAGS) -o kernel.bin $(SOURCES)

.c.o:
	i686-elf-gcc $(CFLAGS) $<
	
.s.o:
	nasm $(ASFLAGS) $<
