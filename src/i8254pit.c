#include "i8254pit.h"
#include "arch64.h"


void i8254pic_setup()
{
    _a64_disable_interrupts();

    // Write command register
    _a64_outb(I8254_CMD_PORT, I8254_CTL_SC0 | I8254_CTL_MODE3 | I8254_CTL_RW_WORD);

    // Write reload value
    unsigned short frequency = 11932*2;
    _a64_outb(I8254_CHANNEL0_PORT, frequency & 0xFF);
    _a64_outb(I8254_CHANNEL0_PORT, (frequency & 0xFF00) >> 8);

    _a64_enable_interrupts();
}
