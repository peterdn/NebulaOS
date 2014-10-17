#ifndef __MULTIBOOT_HEADER__
#define __MULTIBOOT_HEADER__

#include "stdtypes.h"

// Multiboot header info
#define     MULTIBOOT_HEADER_MAGIC      0x1BADB002
#define     MULTIBOOT_HEADER_FLAGS      0x00010003
#define     MULTIBOOT_MAGIC             0x2BADB002

// stack size
#define     STACK_SIZE                  0x4000


#ifndef ASM

typedef struct multiboot_info
{
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    unsigned char syms[16];
    uint32_t nmap_length;
    uint32_t nmap_addr;
    
} multiboot_info_t;

#endif /* ASM */
#endif /* __MULTIBOOT_HEADER__ */
