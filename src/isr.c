#include "arch_types.h"
#include "isr.h"

void kprintf(const char *str, unsigned long long k1);

idt_entry_t idt[32];
idtr_t idtr;

void write_idt_entry(int interrupt_number, void (*isr_routine)())
{
    idt_entry_t *e = &idt[interrupt_number];
    e->d4_32 = 0;
    e->d3_32 = 0;
    unsigned long offset_u = (((unsigned long) isr_routine) & 0xFFFF0000);
    unsigned long offset_l = (((unsigned long) isr_routine) & 0xFFFF);
    e->d2_32 = offset_u | 0x8E00;
    e->d1_32 = offset_l | 0x180000;
}

void initialize_idt()
{
    #include "idt.c"

    idtr.base_address = (unsigned long) &idt[0];
    idtr.table_limit = sizeof(idt);
}

void isr_handler(long interrupt_number, long error_code, long l1, long l2)
{
    kprintf("Got interrupt 0x%X\n", interrupt_number);
    kprintf("Got error code 0x%X\n", error_code);
    kprintf("Got l1 0x%X\n", l1);
    kprintf("Got l2 0x%X\n", l2);
    
    if (interrupt_number == 0)
    {
        kprintf("DIVIDE BY 0...\n", 0);
        for (;;);
    }
    else if (interrupt_number == 14)
    {
        kprintf("Page fault at address 0x%X\n", error_code);
    }
}
