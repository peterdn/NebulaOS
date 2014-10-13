

.text
.align 4
.code32

.globl _enable_segmentation
_enable_segmentation:
        movl %cr0, %eax
        or $0x1, %eax
        movl %eax, %cr0
        movl $0x20, %ebx
        movw %bx, %ds
        movw %bx, %es
        movw %bx, %fs
        movw %bx, %gs
        movw %bx, %ss
        ljmp $0x18, $init_cs

.code64
init_cs:
        call _kernel_main64
 