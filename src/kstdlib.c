#include "kstdlib.h"

int kstrlen(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
        ++i;
    return i;
}

unsigned char * kmemcpy(const unsigned char *src, unsigned char *dest, int nbytes)
{
    unsigned char *end = dest + nbytes;
    while (dest != end)
    {
        *dest++ = *src++;
    }
    return end;
}

void kmemset(unsigned char *dest, unsigned char value, int nbytes)
{
    unsigned char *end = dest + nbytes;
    while (dest != end)
    {
        *dest++ = value;
    }
}

char *itoa(int num, char *dest, int base)
{
    char buffer[20] = "";

    // Only hex or decimal right now.
    base = base == 16 ? base : 10;

    char *b = buffer;
    do
    {
        int r = num % base;
        *b++ = (char) (r < 10 ? r + 0x30 : (r-10) + 0x41);
        num = num / base;
    }
    while (num > 0);

    char *d = dest;
    while (b != buffer)
    {
        *d++ = *--b;
    }

    *d = '\0';
    return dest;
}
