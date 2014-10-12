#ifndef __MULTIBOOT_HEADER__
#define __MULTIBOOT_HEADER__

// Multiboot header info
#define     MULTIBOOT_HEADER_MAGIC      0x1BADB002
#define     MULTIBOOT_HEADER_FLAGS      0x00010003
#define     MULTIBOOT_MAGIC             0x2BADB002

// stack size
#define     STACK_SIZE                  0x4000


#ifndef ASM

typedef struct multiboot_info
{
    unsigned long flags;
    unsigned long mem_lower;
    unsigned long mem_upper;
    unsigned long boot_device;
    unsigned long cmdline;
    unsigned long mods_count;
    unsigned long mods_addr;
    unsigned char syms[16];
    unsigned long nmap_length;
    unsigned long nmap_addr;
    
} multiboot_info_t;

#endif /* ASM */
#endif /* __MULTIBOOT_HEADER__ */
