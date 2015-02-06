#BrenOS 
###A Small x86 Monolithic Kernel

>BrenOS is a toy Operating System built using the GNU Toolset. It is targeted at x86 PC's (System i386 or i686-elf Binary Format). It is meant as a way to get more familiar with building complex toolsets, and the challenge of completing a large, complicated piece of software. 

>Everything needed to compile, build and run BrenOS lie within this directory. Links to the necessary tools (when they are not bundled within this project) will be available. Just follow the instructions. 

###Tools for Building the Kernel:
>Currently, the compiler toolset is tooled to compile to a i686-elf Binary target from a Windows Machine. This requires MinGW for the GNU Resources, and the custom compiled i686-elf-tools compiler toolset. This toolset is a cross-compiler, allowing you to target i686-elf from a non-elf format.

#####MinGW
``` 
Get MinGW: `Available in tools/mingw-get-setup.7z`
Run the installer:
1. Options
  1. Set the installation directory to C:\MinGW
  2. Install the graphical user interface (GUI)
  3. Install for only the user (Keep your other directories clean)
2. Installation manager (runs after installation of the main packages is complete)
  1. msys-base
  2. mingw-32-base
  3. mingw-developer-toolkit
  4. mingw32-gcc-g++
3. Complete the installation by clicking on `Installation > Apply Changes` then `Apply`
```
    	
Get the i686-elf-tools compiler toolset
Install to `C:\i686-elf-tools`
Add to PATH: `C:\i686-elf-tools\bin`

###Building the Kernel:
>Building the Kernel can be done only for Windows machine at the time, as I am currently working on building an i686-elf Cross-Compiler for the Linux platform. Until that happens, the instructions to build the Kernel on Windows are as follows. Ensure that you have the Compilers and MinGW (and any Assemblers, Linkers, .dll's...) with your PATH variable:

    	From ./BrenOS/src	
    		Assembler: `i686-elf-as boot.s -o boot.o`
    		C Compiler: `i686-elf-gcc -c kernel.c -o kernel.o -std=gun99 -ffreestanding -O2 -Wall -Wextra`
    		Linker: `i686-elf-gcc -T link.d -o kernel.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc`

>PUSH ALL YOUR CHANGES TO GIT-HUB HERE TO MAKE THE ISO
	
    	From A Linux Machine
		Pull the changes to the kernel down
		Run _Making the Bootable ISO_
	

	
###Making the Bootable ISO:

	From A Linux Machine:
		Run this command from the root directory of the project
		sudo sh make_iso.sh
	
###Running the Kernel:

	From A Linux Machine:
		Use Qemu
			sudo qemu-system-i386 -kernel src/kernel.bin
			sudo qemu-system-i386 -cdrom BrenOS.iso

- From A Windows Machine:
	- TO-DO...
	
