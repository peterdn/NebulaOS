
.macro DEFINE_ISR n
.globl __a64_isr_\n
__a64_isr_\n:
        cli
        pushq $0        // push fake error code
        pushq $\n       // push interrupt number
        jmp __a64_isr_handler
.endm

.macro DEFINE_ERROR_CODE_ISR n
.globl __a64_isr_\n
__a64_isr_\n:
        cli
        subq $0x8, %rsp
        pushq $\n       // push interrupt number
        jmp __a64_isr_handler
.endm

__a64_isr_handler:
        // Save state of everything...!
        pushq %rdi
        pushq %rsi
        movq 0x10(%rsp), %rdi   // interrupt number
        movq 0x18(%rsp), %rsi   // error code
        movq %cr2, %rdx   // interrupt number
        movq %cr2, %rcx   // error code
        pushq %rcx
        pushq %rdx
        pushq %rbp
        pushq %rax
        pushq %rbx
        pushq %r8
        pushq %r9
        pushq %r10
        pushq %r11
        pushq %r12
        pushq %r13
        pushq %r14
        pushq %r15
        call _isr_handler
        popq %r15
        popq %r14
        popq %r13
        popq %r12
        popq %r11
        popq %r10
        popq %r9
        popq %r8
        popq %rbx
        popq %rax
        popq %rbp
        popq %rdx
        popq %rcx
        popq %rsi
        popq %rdi
        add $0x10, %rsp
        sti
        iretq


/* Intel exception ISRs */
DEFINE_ISR 0                // Divide by zero
DEFINE_ISR 1                // RESERVED
DEFINE_ISR 2                // NMI interrupt
DEFINE_ISR 3                // Breakpoint
DEFINE_ISR 4                // Overflow
DEFINE_ISR 5                // BOUND range exceeded
DEFINE_ISR 6                // Invalid opcode
DEFINE_ISR 7                // No math coprocessor
DEFINE_ERROR_CODE_ISR 8     // Double fault
DEFINE_ISR 9                // Coprocessor segment overrun
DEFINE_ERROR_CODE_ISR 10    // Invalid TSS
DEFINE_ERROR_CODE_ISR 11    // Segment not present
DEFINE_ERROR_CODE_ISR 12    // Stack-segment fault
DEFINE_ERROR_CODE_ISR 13    // General protection
DEFINE_ERROR_CODE_ISR 14    // Page fault
DEFINE_ISR 15               // RESERVED
DEFINE_ISR 16               // Math fault (x87)
DEFINE_ERROR_CODE_ISR 17    // Alignment check
DEFINE_ISR 18               // Machine check
DEFINE_ISR 19               // SIMD floating point exception
DEFINE_ISR 20               // Virtualization exception

// GAS macro documentation is terrible.
// .altmacro lets us convert number i to string %i.
.altmacro
.macro DEFINE_USER_ISRS from, to
i = \from
n = \to - \from + 1
.rept n
DEFINE_ISR %i
i = i + 1
.endr
.endm

DEFINE_USER_ISRS 21, 31     // RESERVED

DEFINE_USER_ISRS 32, 255    // User defined
