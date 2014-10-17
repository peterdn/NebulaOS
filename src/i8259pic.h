#ifndef __I8259PIC_HEADER__
#define __I8259PIC_HEADER__


#define I8259_MASTER_CMD_PORT       0x20
#define I8259_MASTER_DATA_PORT      0x21
#define I8259_SLAVE_CMD_PORT        0xA0
#define I8259_SLAVE_DATA_PORT       0xA1

#define I8259_EOI                   0x20    // End of interrupt control code

#define I8259_ICW1_ICW4             0x01
#define I8259_INIT                  0x10
#define I8259_ICW4_8086             0x01



void i8259pic_set_mask(int bit);
void i8259pic_mask_all_interrupts();
void i8259pic_remap();
void i8259pic_send_eoi();


#endif // __I8259PIC_HEADER__
