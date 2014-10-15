
/**
 * Generic getter/setters for control registers.
 */
.macro DEFINE_CR_GET_SET n
.globl __a32_get_cr\n
__a32_get_cr\n:
        movl %cr\n, %eax
        ret

.globl __a32_set_cr\n
__a32_set_cr\n:
        movl 0x4(%esp), %eax    // First parameter is value to set.
        movl %eax, %cr\n
        ret
.endm

DEFINE_CR_GET_SET 0
DEFINE_CR_GET_SET 1
DEFINE_CR_GET_SET 2
DEFINE_CR_GET_SET 3


/**
 * Returns value of IA32_EFER register.
 */
.globl __a32_get_ia32_efer
__a32_get_ia32_efer:
        movl $0xC0000080, %ecx
        rdmsr
        ret

/**
 * Sets CR4.PAE bit to enable physical address extension (PAE).
 */
.globl __a32_enable_pae
__a32_enable_pae:
        movl %cr4, %eax
        or $0x20, %eax
        movl %eax, %cr4
        ret


/**
 * Sets IA32_EFER.LME bit to enable IA-32e mode.
 */
.globl __a32_enable_ia32e_mode
__a32_enable_ia32e_mode:
        movl $0xC0000080, %ecx
        rdmsr
        or $0x100, %eax
        wrmsr
        ret


/**
 * Sets CR0.PG bit to enable paging.
 */
.globl __a32_enable_paging
__a32_enable_paging:
        movl %cr0, %eax
        or $(1 << 31), %eax
        movl %eax, %cr0
        ret


/**
 * Loads the GDTR register and enters a
 * 64-bit code segment at the specified address.
 */
.globl __a32_set_ia32e_gdtr_and_enter
__a32_set_ia32e_gdtr_and_enter:
        movl 0x4(%esp), %eax    // Address of 64-bit procedure.
        movl 0x8(%esp), %edx    // GDT limit in bytes.
        shl $16, %edx
        movl %edx, 0x8(%esp)    // Move limit to upper word.
        lgdtl 0xA(%esp)         // Load GDTR from 6 bytes 0xA(%esp)->0xF(%esp).
        movl $0x20, %ebx        // Kernel mode data segment selector.
        movw %bx, %ds
        movw %bx, %es
        movw %bx, %fs
        movw %bx, %gs
        movw %bx, %ss
        ljmp $0x18, $init_cs    // Far jump to 64-bit kernel code segment.

/* Theoretically we should be in 64-bit mode at this point... */
.code64
init_cs:
        call *%rax              // Call our 64-bit entry procedure.
