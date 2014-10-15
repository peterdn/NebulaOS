#include "arch_types.h"

void kcls();
void kprintf(const char *str, unsigned long long k1);
int kstrlen(const char *str);

extern gdt_t gdt;

void initialize_tss();
void initialize_idt();
void _a64_set_tr();
void _a64_set_idtr();

void kinit64()
{
    kcls();
    kprintf("Nebula 64-bit OS v0.1\n", 0);

    initialize_tss();
    _a64_set_tr();

    initialize_idt();
    _a64_set_idtr();

    int x = 5;
    int s = kstrlen("");

    int r = x/s;

    kprintf("This happens after the exception\n", 0);

    for(;;);
}

void initialize_tss()
{
    gdt.tss.gdt_entry_l.d_64 = 0;
    gdt.tss.d_64 = 0;

    // base at 0x203000
    // see page 1999 of massive intel book
    gdt.tss.gdt_entry_l.l_32 = 0x03000000 + 104;
    gdt.tss.gdt_entry_l.base_address_23_16 = 0x20;
    gdt.tss.gdt_entry_l.segment_type = 9;   // 64-bit TSS (available)
    gdt.tss.gdt_entry_l.segment_present = 1;
}
