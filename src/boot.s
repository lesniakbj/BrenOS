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

global gdt_flush
extern g_ptr
gdt_flush:
	lgdt [g_ptr]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush2

flush2:
	ret
	
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

isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common

isr2:
	cli
	push byte 0
	push byte 2
	jmp isr_common
	
isr3:
	cli
    push byte 0
    push byte 3
    jmp isr_common
	
isr4:
	cli
    push byte 0
    push byte 4
    jmp isr_common
	
isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common
	
isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common

isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common

isr8:
    cli
    push byte 8        ; Note that we DON'T push a value on the stack in this one!
						; It pushes one already! Use this type of stub for exceptions
						; that pop error codes!
    jmp isr_common
				
isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common

isr10:
    cli
    push byte 10
    jmp isr_common

isr11:
    cli
    push byte 11
    jmp isr_common

isr12:
    cli
    push byte 12
    jmp isr_common

isr13:
    cli
    push byte 13
    jmp isr_common

isr14:
    cli
    push byte 14
    jmp isr_common

isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common

isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common

isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_common

isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common


isr19:
	cli
    push byte 0
    push byte 19
    jmp isr_common


isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common

isr21:
	cli
    push byte 0
    push byte 21
    jmp isr_common

isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common


isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common


isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common

isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common

isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common

isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common

isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common


isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common

isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common


isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common
				
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