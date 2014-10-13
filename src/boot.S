/*
    boot.S - bootstrapper entry point
*/

#define ASM
#include "multiboot.h"

.text
.align 4
.code32

/* multiboot header */
multiboot_header:
.long MULTIBOOT_HEADER_MAGIC
.long MULTIBOOT_HEADER_FLAGS
.long -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
.long multiboot_header
.long multiboot_header
.long 0
.long _end
.long boot_entry

/* our actual boot entry point */
.globl boot_entry
boot_entry:
        movl $(stack + STACK_SIZE), %esp    /* set up the stack */
        pushl %ebx                          
        pushl %eax
        call _cboot_main32                  /* our C entry */



.globl _get_cr0
_get_cr0:
        movl %cr0, %eax
        ret


.globl _get_ia32_efer
_get_ia32_efer:
        movl $0xC0000080, %ecx
        rdmsr
        ret


.globl _enable_pae
_enable_pae:
        movl %cr4, %eax
        or $0x20, %eax
        movl %eax, %cr4
        ret


.globl _write_cr3
_write_cr3:
        movl $0x200000, %eax
        movl %eax, %cr3
        ret


.globl _enable_ia32e_mode
_enable_ia32e_mode:
        movl $0xC0000080, %ecx
        rdmsr
        or $0x100, %eax
        wrmsr
        ret


.globl _enable_paging
_enable_paging:
        movl %cr0, %eax
        or $(1 << 31), %eax
        movl %eax, %cr0
        ret



/* load data into GDT register */
.extern _gdtr
.globl _load_gdtr
_load_gdtr:
        lgdtl _gdtr
        movl $0x20, %ebx
        movw %bx, %ds
        movw %bx, %es
        movw %bx, %fs
        movw %bx, %gs
        movw %bx, %ss
        ljmp $0x18, $init_cs

/* Theoretically we should be in 64-bit mode at this point... */
.code64
init_cs:
        call _kernel_main64


/* stack starts here */
.data
.comm stack, STACK_SIZE
