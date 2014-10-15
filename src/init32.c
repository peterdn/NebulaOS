#include "multiboot.h"
#include "arch_types.h"

// 64-bit GDT.
gdt_t gdt;

// Forward declarations.
void initialize_paging_structures();
void initialize_gdt();
void kinit32(unsigned long magic, multiboot_info_t *info);

// Assembly routines.
void _a32_enable_segmentation();
void _a32_enable_pae();
void _a32_set_cr3(unsigned long value);
void _a32_enable_ia32e_mode();
void _a32_enable_paging();
unsigned int _a32_get_ia32_efer();
void _a32_set_ia32e_gdtr_and_enter(void (*long_main)(void), unsigned int gdt_limit, void *gdt_base_address);
void kinit64();


void kinit32(unsigned long magic, multiboot_info_t *info)
{
    // Enable IA-32e paging and segmentation structures.
    initialize_paging_structures();
    initialize_gdt();

    _a32_enable_pae();
    _a32_set_cr3(0x200000);
    _a32_enable_ia32e_mode();
    _a32_enable_paging();

    // We are now in IA-32e 32-bit compatability mode. 
    // Load the new 64-bit segment descriptors and jump to 64-bit entry.
    _a32_set_ia32e_gdtr_and_enter(kinit64, sizeof(gdt), &gdt);
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
}
