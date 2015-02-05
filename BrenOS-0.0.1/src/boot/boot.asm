[BITS 32]
MBOOT_ALIGN		equ 1<<0
MBOOT_MEM		equ 1<<1
MBOOT_MAGIC		equ 0x1BADB002
MBOOT_FLAGS		equ MBOOT_ALIGN | MBOOT_MEM
MBOOT_CHKSUM	equ -(MBOOT_MAGIC + MBOOT_FLAGS)

SECTION .mboot
ALIGN 4
	dd MBOOT_MAGIC
	dd MBOOT_FLAGS
	dd MBOOT_CHKSUM

SECTION .boot_stack
ALIGN 4
stack_lower:
times 16384 db 0
stack_upper:
	
SECTION .text
global _start
_start:
	mov esp, stack_upper
	
	extern kernel_main
	call kernel_main
	cli
	
.hng:
	hlt
	jmp .hng