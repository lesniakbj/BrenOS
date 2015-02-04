# BrenOS
A Small x86 Monolithic Kernel


Tools for Building the Kernel:
	- From A Windows Machine:
		- Install MinGW & add it to the PATH
			- Available at: [PATH TO MINGW HERE]
			- Install to C:\MinGW
			- Add to PATH: C:\MinGW\bin
		- Get the i686-elf-tools compiler toolset
			- Available at: [PATH TO COMPILER HERE]
			- Install to C:\i686-elf-tools
			- Add to PATH: C:\i686-elf-tools\bin
			
Building the Kernel:
	- From A Windows Machine:
		- Ensure the Compiler is within your PATH
		- From ./BrenOS/src
			- Assembler: i686-elf-as boot.s -o boot.o
			- C Compiler: i686-elf-gcc -c kernel.c -o kernel.o -std=gun99 -ffreestanding -O2 -Wall -Wextra
			- Linker: i686-elf-gcc -T link.d -o kernel.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
			
			[PUSH ALL YOUR CHANGES TO GIT-HUB HERE TO MAKE THE ISO]
	- From A Linux Machine
		- Pull the changes to the kernel down
		- Run [Making the Bootable ISO]
	
Making the Bootable ISO:
	- From A Linux Machine:
		- Run this command from the root directory of the project
			- sudo sh make_iso.sh
	
Running the Kernel:
	- From A Linux Machine:
		- Use Qemu
			- sudo qemu-system-i386 -kernel src/kernel.bin
			- sudo qemu-system-i386 -cdrom BrenOS.iso
	
	- From A Windows Machine:
		- TO-DO...
	
