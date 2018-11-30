# Declare constants for multiboot header.
.set ALIGN,     1<<0            # Align loaded modules on page boundaries
.set MEMINFO,   1<<1            # Provide memory map
.set FLAGS,     ALIGN | MEMINFO # Multiboot 'flag' field
.set MAGIC,     0x1BADB002      # bootloader magic num
.set CHECKSUM,  -(MAGIC + FLAGS)# Checksum to prove we are multiboot

# Declare the multiboot header.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve stack for initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# Kernel entry point
.section .text
.global _start
.type _start, @function
_start:
movl $stack_top, %esp

# Call the global constructors.
call _init

# Transfer control to the main kernel.
call kernel_main

# Hang if kernel_main returns unexpectedly.
cli
hang:
    hlt
    jmp hang
.size _start, . - _start
