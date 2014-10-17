#include "i8259pic.h"
#include "arch64.h"



/* Programmable Interrupt Controller */

void i8259pic_send_eoi(int irq)
{
    if (irq >= 8)
        _a64_outb(I8259_SLAVE_CMD_PORT, I8259_EOI);

    _a64_outb(I8259_MASTER_CMD_PORT, I8259_EOI);
}

void i8259pic_remap()
{
    unsigned char master_mask = _a64_inb(I8259_MASTER_DATA_PORT);
    unsigned char slave_mask = _a64_inb(I8259_SLAVE_DATA_PORT);

    // Send initialization command to both slave and master
    _a64_outb(I8259_MASTER_CMD_PORT, I8259_INIT | I8259_ICW1_ICW4);
    _a64_io_wait();
    _a64_outb(I8259_SLAVE_CMD_PORT, I8259_INIT | I8259_ICW1_ICW4);
    _a64_io_wait();

    // Send vector offset...
    _a64_outb(I8259_MASTER_DATA_PORT, 0x20);
    _a64_io_wait();
    _a64_outb(I8259_SLAVE_DATA_PORT, 0x28);
    _a64_io_wait();    

    // Setup slave
    // Tell master slave is on IRQ 2
    _a64_outb(I8259_MASTER_DATA_PORT, 4);
    _a64_io_wait();
    // Slave's cascade identity
    _a64_outb(I8259_SLAVE_DATA_PORT, 2);
    _a64_io_wait();

    _a64_outb(I8259_MASTER_DATA_PORT, I8259_ICW4_8086);
    _a64_io_wait();
    _a64_outb(I8259_SLAVE_DATA_PORT, I8259_ICW4_8086);
    _a64_io_wait();

    // Reassign masks
    _a64_outb(I8259_MASTER_DATA_PORT, master_mask);
    _a64_outb(I8259_SLAVE_DATA_PORT, slave_mask);
}

void i8259pic_mask_all_interrupts()
{
    _a64_outb(I8259_MASTER_DATA_PORT, 0xFF);
    _a64_outb(I8259_SLAVE_DATA_PORT, 0xFF);
}

void i8259pic_set_mask(int bit)
{    
    unsigned short port = I8259_MASTER_DATA_PORT;
    if (bit > 7)
    {
        port = I8259_SLAVE_DATA_PORT;
        bit -= 8;
    }

    unsigned char mask = _a64_inb(port);
    _a64_outb(port, mask & ~(1 << bit));
}
