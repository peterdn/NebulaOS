#ifndef __ARCH_TYPES_H__
#define __ARCH_TYPES_H__

#include "stdtypes.h"

typedef struct gdtr_s
{
    uint16_t table_limit;
    void *base_address;
} __attribute__((packed)) gdtr_t;


typedef struct idtr_s
{
    uint16_t table_limit;
    void *base_address;
} __attribute__((packed)) idtr_t;


typedef struct idt_entry_s
{
    uint32_t d1_32;
    uint32_t d2_32;
    uint32_t d3_32;
    uint32_t d4_32;
} __attribute__((packed)) idt_entry_t;


typedef union gdt_entry_s
{
    struct
    {
        unsigned segment_limit_15_0     : 16;
        unsigned base_address_15_0      : 16;
        unsigned base_address_23_16     : 8;
        unsigned segment_type           : 4; 
        unsigned descriptor_type        : 1;
        unsigned privilege_level        : 2;
        unsigned segment_present        : 1;
        unsigned segment_limit_19_16    : 4;
        unsigned available              : 1;
        unsigned long_code_segment      : 1;
        unsigned default_opsize         : 1;
        unsigned granularity            : 1;
        unsigned base_address_31_24     : 8;
    } __attribute__((packed));

    struct
    {
        uint32_t l_32;
        uint32_t u_32;
    } __attribute__((packed));

    uint64_t d_64;

} __attribute__((packed)) gdt_entry_t;


typedef struct tss_gdt_entry_s
{
    gdt_entry_t gdt_entry_l;

    union
    {
        struct 
        {
            unsigned base_address_63_32         : 32;

            union
            {
                struct
                {
                    unsigned reserved_7_0       : 8;
                    unsigned zero_flags         : 5;
                    unsigned reserved_31_13     : 19;
                } __attribute__((packed));

                unsigned reserved_31_0          : 32;
            } __attribute__((packed));
        } __attribute__((packed));

        uint64_t d_64;
    } __attribute__((packed));

} __attribute__((packed)) tss_gdt_entry_t;


typedef union gdt_s
{
    struct
    {
        gdt_entry_t null;
        tss_gdt_entry_t tss;
        gdt_entry_t kernel_code;
        gdt_entry_t kernel_data;
        gdt_entry_t user_code;
        gdt_entry_t user_data;
    } __attribute__((packed));

    gdt_entry_t entries[6];

} __attribute__((aligned(8), packed)) gdt_t;



typedef union pml4_entry_s
{
    struct
    {
        unsigned present                    : 1;
        unsigned read_write                 : 1;
        unsigned user_supervisor            : 1;
        unsigned page_level_write_through   : 1;
        unsigned page_level_cache_disable   : 1;
        unsigned accessed                   : 1;
        unsigned ignored_reserved_1         : 6;
        unsigned long long address          : 39;
        unsigned ignored_reserved_2         : 12;
        unsigned execute_disable            : 1;
    } __attribute__((packed));

    uint64_t d64;

} __attribute__((packed)) pml4_entry_t;



typedef union pdpt_entry_s
{
    struct
    {
        unsigned present                    : 1;
        unsigned read_write                 : 1;
        unsigned user_supervisor            : 1;
        unsigned page_level_write_through   : 1;
        unsigned page_level_cache_disable   : 1;
        unsigned accessed                   : 1;
        unsigned ignored_reserved_1         : 1;
        unsigned page_size                  : 1;
        unsigned ignored_reserved_2         : 4;
        unsigned long long address          : 39;
        unsigned ignored_reserved_3         : 12;
        unsigned execute_disable            : 1;
    } __attribute__((packed));

    uint64_t d64;

} __attribute__((packed)) pdpt_entry_t;



typedef union pd_entry_2mb_page_s
{
    struct
    {
        unsigned present                    : 1;
        unsigned read_write                 : 1;
        unsigned user_supervisor            : 1;
        unsigned page_level_write_through   : 1;
        unsigned page_level_cache_disable   : 1;
        unsigned accessed                   : 1;
        unsigned dirty                      : 1;
        unsigned page_size                  : 1;
        unsigned global                     : 1;
        unsigned ignored_reserved_1         : 3;
        unsigned pat                        : 1;
        unsigned ignored_reserved_2         : 8;
        unsigned address                    : 30;
        unsigned ignored_reserved_3         : 12;
        unsigned execute_disable            : 1;
    } __attribute__((packed));

    uint64_t d64;

} __attribute__((packed)) pd_entry_2mb_page_t;


#define PAGE_PRESENT    1
#define PAGE_WRITABLE   2
#define PAGE_USERMODE   4
#define PAGE_SIZE       128


#endif /* __ARCH_TYPES_H__ */