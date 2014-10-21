// TODO: move to .c __asm__ __volatile__ blocks.

.code64

/**
 * Generic getter/setters for control registers.
 */
.macro DEFINE_CR_GET_SET n
.globl __a64_get_cr\n
__a64_get_cr\n:
        movq %cr\n, %rax
        ret

.globl __a64_set_cr\n
__a64_set_cr\n:
        movl %rdi, %cr\n
        ret
.endm


.globl __a64_outb
__a64_outb:
        movw %di, %dx
        movw %si, %ax
        outb %al, %dx
        retq

.globl __a64_inb
__a64_inb:
        movw %di, %dx
        inb %dx, %al
        retq

.globl __a64_io_wait
__a64_io_wait:
        // apparently port 0x80 is used for POST checkpoints?
        movb $0, %al
        outb %al, $0x80
        retq


.globl __a64_set_tr
__a64_set_tr:
        movw $0x8, %ax
        ltr %ax
        retq


.globl __a64_set_idtr
__a64_set_idtr:
        lidt _idtr
        retq


.extern _user_func
.globl __a64_exec
__a64_exec:
        // Write current rsp to RSP0 in TSS
        movq %rsp, 0x203004
        movw $0x33, %bx
        movw %bx, %ds
        movw %bx, %es
        movw %bx, %fs
        movw %bx, %gs
        //movw %bx, %ss
        push $0x33
        push $0x800000
        push $0x2b
        push $_user_func
        movq $0x400000, %rax
        movq %rax, %cr3
        movq $2, %rax
        sti
        //ljmp *ptr_user_func
        lretq


ptr_user_func:
.quad _user_func
.short 0x28
