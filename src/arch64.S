

.globl __a64_set_tr
__a64_set_tr:
        movw $0x8, %ax
        ltr %ax
        retq


.globl __a64_set_idtr
__a64_set_idtr:
        lidt _idtr
        retq

