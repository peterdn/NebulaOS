BINDIR=../bin
OBJDIR=../obj

ASMSRCS=arch64.S \
        isr64.S 

CSRCS=init64.c \
        kstdio.c \
        isr.c \
        i8259pic.c \
        i8254pit.c \
        kstdlib.c \
        user.c

ASMSRCS32=boot.S \
          arch32.S \

CSRCS32=init32.c


COBJS=$(CSRCS:.c=.o)
ASMOBJS=$(ASMSRCS:.S=.o)
COBJS32=$(CSRCS32:.c=.o)
ASMOBJS32=$(ASMSRCS32:.S=.o)

OBJS=$(ASMOBJS:%.o=$(OBJDIR)/%.o) $(COBJS:%.o=$(OBJDIR)/%.o)
OBJS32=$(ASMOBJS32:%.o=$(OBJDIR)/%.o) $(COBJS32:%.o=$(OBJDIR)/%.o)


CFLAGS=-Wall -Werror -fno-stack-protector -fleading-underscore -std=c99
LDFLAGS=-Ttext 0x100000 -Tdata 0x180000 --entry boot_entry



all: init $(COBJS) $(ASMOBJS) $(COBJS32) $(ASMOBJS32) link32 link64 binary

init:
		mkdir -p $(OBJDIR)

$(COBJS): %.o: %.c
		cc $(CFLAGS) -c $< -o $(OBJDIR)/$@

$(ASMOBJS): %.o: %.S
		mkdir -p $(OBJDIR)
		cc $(CFLAGS) -c $< -o $(OBJDIR)/$@

$(COBJS32): %.o: %.c
		mkdir -p $(OBJDIR)
		cc -m32 $(CFLAGS) -c $< -o $(OBJDIR)/$@

$(ASMOBJS32): %.o: %.S
		mkdir -p $(OBJDIR)
		cc -Wa,--32 $(CFLAGS) -c $< -o $(OBJDIR)/$@

link32:
		ld -i -melf_i386 -o $(OBJDIR)/boot32.o $(OBJS32)
		objcopy -O elf64-x86-64 $(OBJDIR)/boot32.o $(OBJDIR)/boot32_64.o

link64:
		ld $(LDFLAGS) -o $(OBJDIR)/kernel.elf $(OBJDIR)/boot32_64.o $(OBJS)

binary:
		mkdir -p $(BINDIR)
		objcopy -O binary $(OBJDIR)/kernel.elf $(BINDIR)/kernel


clean:
		rm -f *.o *.elf
		rm -rf $(BINDIR)
		rm -rf $(OBJDIR)
