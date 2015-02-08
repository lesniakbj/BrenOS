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
	
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

isr0:
	cli
	push byte 0
	push byte 0
	
	jmp isr_common
	
;  1: Debug Exception
isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common
    
; Fill in from 2 to 7 here!
isr2:
isr3:
isr4:
isr5:
isr6:
isr7:

;  8: Double Fault Exception (With Error Code!)
isr8:
    cli
    push byte 8        ; Note that we DON'T push a value on the stack in this one!
                ; It pushes one already! Use this type of stub for exceptions
                ; that pop error codes!
    jmp isr_common

				; You should fill in from _isr9 to _isr31 here. Remember to
                ; use the correct stubs to handle error codes and push dummies!
				
isr9:
isr10:
isr11:
isr12:
isr13:
isr14:
isr15:
isr16:
isr17:
isr18:
isr19:
isr20:
isr21:
isr22:
isr23:
isr24:
isr25:
isr26:
isr27:
isr28:
isr29:
isr30:
isr31:
				
extern fault_handler

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
isr_common:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp   ; Push us the stack
    push eax
    mov eax, fault_handler
    call eax       ; A special call, preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!