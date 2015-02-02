SOURCES = boot.o main.o
CFLAGS = -nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS = -T link.ld
ASFLAGS = -f efl32

all: $(SOURCES) link

clean:
	-rm *.o kernel.bin

link:
	ld $(LDFLAGS) -o kernel.bin $(SOURCES)
	
.asm.o:
	nasm $(ASFLAGS) $<
