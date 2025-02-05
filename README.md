#BrenOS 
###A Small x86 Monolithic Kernel

>BrenOS is a toy Operating System built using the GNU Toolset. It is targeted at x86 PC's (System i386 or i686-elf Binary Format). It is meant as a way to get more familiar with building complex toolsets, and the challenge of completing a large, complicated piece of software. 

>Everything needed to compile, build and run BrenOS lie within this directory. Links to the necessary tools (when they are not bundled within this project) will be available. Just follow the instructions. 

###Tools for Building the Kernel:
>Currently, the compiler toolset is tooled to compile to a i686-elf Binary target from a Windows Machine. This requires MinGW for the GNU Resources, and the custom compiled i686-elf-tools compiler toolset. This toolset is a cross-compiler, allowing you to target i686-elf from a non-elf format.

####MinGW
>######Get MinGW: `Available in tools/mingw-get-setup.7z`
```
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
######Add the toolset to the system PATH: `C:\MinGW\bin`
```
1. Windows 8
  1. Hit the windows key on the keyboard
  2. Search for "System"
  3. Click on "Advanced System Settings"
  4. ... Enviorment Variables...
  5. Find PATH or Path
    1. Click `Edit`
    2. At the end of the current variables present put a ";"
    3. Add `C:\MinGW\bin;`
2. Windows 7
  1. COMING SOON
```

####i686-elf-tools
>######Get the i686-elf-tools: `Available in tools/i686-elf-tools.7z`
```
1. Unzip to `C:\i686-elf-tools`
```
######Add the toolset to the system PATH: `C:\i686-elf-tools\bin`
```
1. Windows 8
  1. Hit the windows key on the keyboard
  2. Search for "System"
  3. Click on "Advanced System Settings"
  4. ... Enviorment Variables...
  5. Find PATH or Path
    1. Click `Edit`
    2. At the end of the current variables present put a ";"
    3. Add `C:\i686-elf-tools\bin;`
2. Windows 7
  1. COMING SOON
```

####NASM
>######Get the i686-elf-tools: `Available in tools/nasm-2.11.06.7z`
```
1. Unzip to `C:\nasm-2.11.06`
```
######Add the toolset to the system PATH: `C:\nasm-2.11.06`
```
1. Windows 8
  1. Hit the windows key on the keyboard
  2. Search for "System"
  3. Click on "Advanced System Settings"
  4. ... Enviorment Variables...
  5. Find PATH or Path
    1. Click `Edit`
    2. At the end of the current variables present put a ";"
    3. Add `C:\nasm-2.11.06;`
2. Windows 7
  1. COMING SOON
```

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
>######NOTE: This section MAY BE SKIPPED if you would like to run the kernel as a `.bin`
```
1.From A Linux Machine:
  1.Run this command from the root directory of the project
  2.sudo sh make_iso.sh
```

###Running the Kernel:
>There are a few different methods that you can run the kernel. There are instructions that follow for 2 different flavors of vitrual machines (QEmu and Hyper-V) and how to run this on real hardware. The kernel does not need a full ISO image in order to it to be run (on virtual hardware), and it can simply be ran with the .bin binary file. To do either, follow the instructions below. 

####QEmu
```
TO COME...
```
