# Multiboot constants needed for booting
.set ALIGN,		1<<0
.set MEMINFO,	1<<1
.set FLAGS,		ALIGN | MEMINFO
.set MAGIC,		0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

# Decalre the multiboot header struct
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for Kernel StartUp
stack_bottom:
.skip 16384		# 16 KiB
stack_top:

# Main Kernel Entry Point
.section .text
.global _start
.type _start, @function
_start:
	
	# Move the stack location into the stack pointer register
	movl $stack_top, %esp
	
	# Initialize the core of the Kernel before Global Constructors
	call pre_init_kernel
	
	# Initialize the Global Constructors
	call _init_globals
	
	# ...and back to the Kernel
	call kernel_main
	
	# Hang if it returns...
	cli
	hlt
.Lhang:
	jmp .Lhang
.size _start, . - _start