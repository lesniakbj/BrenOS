[BITS 32]
MBALIGN     equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MBALIGN | MEMINFO      ; this is the Multiboot 'flag' field
MAGIC       equ  0x1BADB002             ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum of above, to prove we are multiboot
 
global multiboot

SECTION multiboot
ALIGN 4
multiboot:
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
	dd  multiboot                    ; Location of this descriptor
	dd  _start                     ; Kernel entry point (initial EIP).


SECTION .bootstrap_stack
ALIGN 4
stack_bottom:
times 16384 db 0
stack_top:
 

SECTION .text
global _start
_start:

	mov esp, stack_top
 
	push ebx
	extern kern_main
	call kern_main

	cli
.hang:
	hlt
	jmp .hang

global idt_load
extern i_ptr
idt_load:
	lidt [i_ptr]
	ret