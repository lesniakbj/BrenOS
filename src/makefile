SOURCES = shell.o kernel.o core.o screen.o
LDFLAGS = -T link.ld -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
ASFLAGS = -f elf32
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra

all: $(SOURCES) link

clean: 
	-rm *.o kernel.bin