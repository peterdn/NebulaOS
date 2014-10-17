

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


.globl __a64_enable_interrupts
__a64_enable_interrupts:
        sti
        retq


.globl __a64_disable_interrupts
__a64_disable_interrupts:
        sti
        retq
