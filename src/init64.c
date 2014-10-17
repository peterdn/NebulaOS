#include "arch_types.h"
#include "kstdio.h"
#include "kstdlib.h"
#include "isr.h"

#include "i8259pic.h"
#include "i8254pit.h"
#include "arch64.h"



extern gdt_t gdt;

void initialize_tss();


void kinit64()
{
    kcls();
    kprintf("Nebula 64-bit OS v0.1\n", 0);

    initialize_tss();
    _a64_set_tr();

    initialize_idt();
    _a64_set_idtr();

    // Set up PIC
    // TODO: APIC
    i8259pic_mask_all_interrupts();
    i8259pic_remap();

    // enable interrupts    
    _a64_enable_interrupts();
    i8259pic_set_mask(1);

    // Set up PIT
    i8254pic_setup();
    i8259pic_set_mask(0);


    kprintf("Seriously...\n", 0);

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
