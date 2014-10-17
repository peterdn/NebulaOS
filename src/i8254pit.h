#ifndef __I8254PIT_HEADER__
#define __I8254PIT_HEADER__

// i8254 PIT I/O ports
#define I8254_CHANNEL0_PORT     0x40
#define I8254_CHANNEL1_PORT     0x41
#define I8254_CHANNEL2_PORT     0x42
#define I8254_CMD_PORT          0x43

// Control word flags
// Select channel
#define I8254_CTL_SC0           0               // Channel 0 (connected to IRQ 0)
#define I8254_CTL_SC1           (1 << 6)        // Channel 1
#define I8254_CTL_SC2           (2 << 6)        // Channel 2
#define I8254_CTL_READBACK      (3 << 6)        // Readback command

// Read/write flags
#define I8254_CTL_LATCH         0               // Counter latch
#define I8254_CTL_RW_LO         (1 << 4)        // Read/write low byte only
#define I8254_CTL_RW_HI         (2 << 4)        // Read/write high byte only
#define I8254_CTL_RW_WORD       (3 << 4)        // Read/write low followed by high

// Timer mode
#define I8254_CTL_MODE0         0               // Interrupt on terminal count
#define I8254_CTL_MODE1         (1 << 1)        // Hardware retriggerable 1-shot
#define I8254_CTL_MODE2         (2 << 1)        // Rate generator
#define I8254_CTL_MODE3         (3 << 1)        // Square wave mode
#define I8254_CTL_MODE4         (4 << 1)        // Software triggered strobe
#define I8254_CTL_MODE5         (5 << 1)        // Hardware triggered strobe



void i8254pic_setup();

#endif // __I8254PIT_HEADER__
