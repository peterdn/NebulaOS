#include "multiboot.h"
#include "arch_types.h"


gdt_t gdt;
gdtr_t gdtr;


void initialize_paging_structures();
void initialize_gdt();
void cboot_main32(unsigned long magic, multiboot_info_t *info);
extern void enable_segmentation();
extern void enable_pae();
extern void write_cr3();
extern void enable_ia32e_mode();
extern void enable_paging();
extern unsigned int get_ia32_efer();
extern unsigned int get_cr0();
extern void k32printf(char *str, ...);
extern void k32cls();
extern void load_gdtr();

void cboot_main32(unsigned long magic, multiboot_info_t *info)
{
    k32cls();

    initialize_paging_structures();
    k32printf("*** Paging structures initialized ***\n");

    enable_pae();
    k32printf("*** PAE enabled ***\n");

    write_cr3();
    k32printf("*** CR3 allegedly written ***\n");

    enable_ia32e_mode();
    k32printf("*** IA-32e mode initialized ***\n");

    enable_paging();
    k32printf("*** Paging enabled ***\n");

    int ia32_efer = get_ia32_efer();
    if (ia32_efer & 0x400)
    {
        k32printf("IA-32e mode is active! :-D (IA32_EFER = %X)\n", ia32_efer);
    }
    else
    {
        k32printf("IA-32e mode is not active! :-( (IA32_EFER = %X)\n", ia32_efer);
    }

    initialize_gdt();

    load_gdtr();
}


void initialize_paging_structures()
{
    // Map first 16mb identity (8x2mb pages)
    // Page directory at 0x202000
    pd_entry_2mb_page_t *page = (pd_entry_2mb_page_t *) 0x202000;
    for (int i = 0; i < 8; ++i) 
    {
        page[i].d64 = (i * 0x200000) | PAGE_PRESENT | PAGE_WRITABLE | PAGE_SIZE;
        //k32printf("Address of page[i].d64 = 0x%X, val = 0x%X\n", &page[i].d64, (int)page[i].d64);
    }

    // Page directory pointer table at 0x201000
    pdpt_entry_t *pdpte = (pdpt_entry_t *) 0x201000;
    pdpte->d64 = ((unsigned long) page) | PAGE_PRESENT | PAGE_WRITABLE;

    // Page map level 4 table at 2mb
    pml4_entry_t *pml4e = (pml4_entry_t *) 0x200000;
    pml4e->d64 = ((unsigned long) pdpte) | PAGE_PRESENT | PAGE_WRITABLE;

    k32printf("Address of pml4 = 0x%X, val = 0x%X\n", pml4e, (int)pml4e->d64);
}

void initialize_gdt()
{
    // Zero memory
    for (int i = 0; i < 6; ++i)
        gdt.entries[i].d_64 = 0;

    // Base addresses and segment limits for segment descriptors
    for (int i = 3; i < 7; ++i)
    {
        gdt_entry_t *e = &gdt.entries[i];
        e->segment_limit_15_0 = 0xFFFF;
        e->segment_limit_19_16 = 0xF;
        e->segment_present = 1;
        e->granularity = 1;
        e->descriptor_type = 1;
    }

    // Code segments
    gdt.kernel_code.long_code_segment = 1;
    gdt.kernel_code.segment_type = 0xA;
    gdt.user_code.long_code_segment = 1;
    gdt.user_code.segment_type = 0xA;

    // User segments
    gdt.user_code.privilege_level = 3;
    gdt.user_data.privilege_level = 3;

    // Stack data segments
    gdt.kernel_data.default_opsize = 1;
    gdt.kernel_data.segment_type = 2;
    gdt.user_data.default_opsize = 1;
    gdt.user_data.segment_type = 2;

    // GDTR data
    gdtr.table_limit = sizeof(gdt);
    gdtr.base_address = (unsigned int) &gdt;
}