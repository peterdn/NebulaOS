#include "kstdio.h"


void user_func()
{
    kprintf("I'm in a user mode process!\n");

    for (;;);
}