SOURCES = boot.o kernel.o
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T link.ld -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
ASFLAGS = 

all: $(SOURCES) link

clean:
	-rm *.o kernel.bin

link:
	i686-elf-gcc $(LDFLAGS) -o kernel.bin $(SOURCES)

.c.o:
	i686-elf-gcc $(CFLAGS) $<
	
.s.o:
	i686-elf-as $(ASFLAGS) $<
