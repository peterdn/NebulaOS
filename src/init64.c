#include "multiboot.h"

void cboot_main32(unsigned long magic, multiboot_info_t *info)
{
    *((char*)0xB8000) = 'X';
    for(;;);
}
