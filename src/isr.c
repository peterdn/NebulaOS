#include "arch_types.h"
#include "isr.h"
#include "kstdio.h"
#include "i8259pic.h"

idt_entry_t idt[256];
idtr_t idtr;
int ms = 0;

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
    if (interrupt_number == 0)
    {
        kprintf("DIVIDE BY 0...\n", 0);
        for (;;);
    }
    else if (interrupt_number == 33)
    {
        i8259pic_send_eoi(1);
    }
    else if (interrupt_number == 32)
    {
        ms += 10;
        ksetcur(0, 2);
        kprintf("Ms: %X", ms);
        i8259pic_send_eoi(0);
    }
}
