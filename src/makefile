SOURCES = boot.o kernel.o
CFLAGS = -m32 -nostdlib -fno-builtin -fno-stack-protector
LDFLAGS = -m elf_i386 -T link.ld
ASFLAGS = -f elf32

all: $(SOURCES) link

clean:
	-rm *.o kernel.bin

link:
	ld $(LDFLAGS) -o kernel.bin $(SOURCES)
	
.s.o:
	nasm $(ASFLAGS) $<
