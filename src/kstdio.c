#include "kstdio.h"
#include "stdarg.h"



static unsigned char *const vidmem = (unsigned char *) VIDEO_ADDR;
int x = 0;
int y = 0;



void kscroll(int lines)
{
    unsigned char *src = vidmem + (lines * VIDEO_COLS * 2);
    int nbytes = (VIDEO_COLS * 2) * (VIDEO_ROWS - lines);
    unsigned char *dest = kmemcpy(src, vidmem, nbytes);
    kmemset(dest, '\0', VIDEO_COLS * 2 * lines);
}


void kputchar(char c)
{
    switch (c)
    {
    case '\n':
        x = 0;
        ++y;
        break;
    case '\r':
        ++y;
        break;
    case '\t':
        x = ((x / VIDEO_DEFAULT_TAB_SIZE) + 1) * VIDEO_DEFAULT_TAB_SIZE;
        break;
    default:
        vidmem[(y * VIDEO_COLS + x) * 2] = c;
        vidmem[(y * VIDEO_COLS + x) * 2 + 1] = 0x7;
        ++x;
        break;
    }
    
    if (x >= VIDEO_COLS)
    {
        x = 0;
    }

    if (y >= VIDEO_ROWS)
    {
        kscroll(VIDEO_DEFAULT_SCROLL);
        y -= VIDEO_DEFAULT_SCROLL;
    }
}

void ksetcur(int kx, int ky)
{
    x = kx;
    y = ky;
}

void kprintf(const char *str, ...)
{
    va_list list;
    va_start(list, str);

    const char *c = str;

    while (*c != '\0')
    {
        switch (*c)
        {
        case '%':
            if (*(++c) == 'X')
            {
                int k1 = va_arg(list, int);
                char buffer[20];
                kprintf(itoa(k1, buffer, 10));
            }
            break;
        default:
            kputchar(*c);
            break;
        }

        ++c;
    }
}

void kcls()
{
    // assume 80x25
    unsigned char *v = vidmem;
    for (; v < ((unsigned char *) vidmem + 80*25*2); v += 2)
    {
        *v = ' ';
        *(v + 1) = 0x07;
    }

    x = 0; 
    y = 0;
}
