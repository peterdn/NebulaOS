SOURCES=boot64.o kernel64.o

CFLAGS=-fno-stack-protector -fleading-underscore -std=c99
LDFLAGS=-Ttext 0x100000 --entry boot_entry

BINDIR=../bin
OBJDIR=../obj


all: $(SOURCES) boot32 link32 link64 dump

boot32:
		cc -Wa,--32 $(CFLAGS) -c -o boot.o boot.S
		cc -m32 $(CFLAGS) -c -o init64.o init64.c
		cc -m32 $(CFLAGS) -c -o kstdio32.o kstdio32.c

clean:
		rm -f *.o *.elf
		rm -rf $(BINDIR)
		rm -rf $(OBJDIR)

link32:
		ld -i -melf_i386 -o boot32.o boot.o init64.o kstdio32.o
		objcopy -O elf64-x86-64 boot32.o boot32_64.o

link64:
		ld $(LDFLAGS) -o kernel.elf boot32_64.o $(SOURCES)

dump:
		mkdir -p $(BINDIR)
		objcopy -O binary kernel.elf $(BINDIR)/kernel
