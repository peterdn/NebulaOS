#include "arch_types.h"
#include "kstdio.h"
#include "kstdlib.h"
#include "isr.h"

#include "i8259pic.h"
#include "i8254pit.h"
#include "arch64.h"
#include "multiboot.h"



extern gdt_t gdt;
extern multiboot_info_t *multiboot_info;

void initialize_tss();
void initialize_user_paging();
void _a64_exec();

char *str = "";


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


    kprintf("Memory info:\n");
    kprintf("\tLower memory: 0x%X\n\tUpper memory: 0x%X\n\n", 
        (int)multiboot_info->mem_lower, (int)multiboot_info->mem_upper);

    kprintf("Executing user mode process...\n");
    initialize_user_paging();
    _a64_disable_interrupts();
    _a64_exec();

    for(;;);
}

void initialize_tss()
{
    gdt.tss.gdt_entry_l.d_64 = 0;
    gdt.tss.d_64 = 0;

    // base at 0x203000
    // see page 1999 of massive intel book
    gdt.tss.gdt_entry_l.l_32 = 0x30000000 + 104;
    gdt.tss.gdt_entry_l.base_address_23_16 = 0x20;
    gdt.tss.gdt_entry_l.segment_type = 9;   // 64-bit TSS (available)
    gdt.tss.gdt_entry_l.segment_present = 1;
}

void initialize_user_paging()
{
    // Process page database starts at 4mb
    
    // Map first 16mb identity (8x2mb pages)
    // Page directory at 0x402000
    pd_entry_2mb_page_t *page = (pd_entry_2mb_page_t *) 0x402000;
    for (int i = 0; i < 8; ++i) 
    {
        page[i].d64 = (i * 0x200000) | PAGE_PRESENT | PAGE_WRITABLE | PAGE_SIZE | PAGE_USERMODE;
        //k32printf("Address of page[i].d64 = 0x%X, val = 0x%X\n", &page[i].d64, (int)page[i].d64);
    }

    // Page directory pointer table at 0x401000
    pdpt_entry_t *pdpte = (pdpt_entry_t *) 0x401000;
    pdpte->d64 = ((unsigned long) page) | PAGE_PRESENT | PAGE_WRITABLE | PAGE_USERMODE;

    // Page map level 4 table at 4mb
    pml4_entry_t *pml4e = (pml4_entry_t *) 0x400000;
    pml4e->d64 = ((unsigned long) pdpte) | PAGE_PRESENT | PAGE_WRITABLE | PAGE_USERMODE;
}
