/*
    boot.S - bootstrapper entry point
*/

#define ASM
#include "multiboot.h"

.text
.align 4
.code32         /* GRUB dumps us into 32-bit mode with paging disabled */

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
        cli                                 /* disable interrupts */
        movl $(stack + STACK_SIZE), %esp    /* set up the stack */
        pushl %ebx                          
        pushl %eax
        call kinit32                       /* our C entry */


/* stack starts here */
.data
.comm stack, STACK_SIZE
