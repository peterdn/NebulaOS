#ifndef __ARCH64_HEADER__
#define __ARCH64_HEADER__


#ifndef ASM

static inline void _a64_enable_interrupts()
{
    __asm__ __volatile__ ("sti");
}

static inline void _a64_disable_interrupts()
{
    __asm__ __volatile__ ("cli");
}


void _a64_outb(unsigned short port, unsigned char data);
unsigned char _a64_inb(unsigned short port);
void _a64_io_wait();
void _a64_set_tr();
void _a64_set_idtr();


#endif // ASM
#endif // __ARCH64_HEADER__
