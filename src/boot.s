MBALIGN		equ 1 << 0
MEMINFO		equ 1 << 1
FLAGS		equ MBALIGN | MEMINFO
MAGIC		equ 0x1BADB002
CHECKSUM	equ -(MAGIC + FLAGS)

[BITS 32]
[GLOBAL multiboot]
[EXTERN code]
[EXTERN bss]
[EXTERN end]

multiboot:
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
	dd multiboot
	dd code
	dd bss
	dd end
	dd start
	
[GLOBAL start]
[EXTERN main]

start:
	push ebx
	cli
	call main
	jmp $
