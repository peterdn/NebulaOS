
#define VIDEO_MEMORY_ADDR 0xB8000

int x;
int y;


void kprintf(const char *str, unsigned long long k1);

int kstrlen(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
        ++i;
    return i;
}

void kcur(int kx, int ky)
{
    x = kx;
    y = ky;
}

void kprinthex(unsigned long long hexnum)
{
    char buffer[20] = "";
    char rbuffer[20] = "";

    int i = 0;
    do
    {
        int r = hexnum % 0x10;
        buffer[i++] = (char) (r < 10 ? r + 0x30 : (r-10) + 0x41);
        hexnum = hexnum / 0x10; 
    }
    while (hexnum > 0);

    char *b = buffer + kstrlen(buffer);
    char *r = rbuffer;
    while (b-- != buffer)
    {
        *r++ = *b;
    }

    kprintf(rbuffer, 0);
}


void kprintf(const char *str, unsigned long long k1)
{
    unsigned char *vidmem = (unsigned char *) VIDEO_MEMORY_ADDR;
    const char *c = str;

    while (*c != '\0')
    {
        switch (*c)
        {
        case '\n':
            ++y;
            x = 0;
            break;
        case '%':
            if (*(++c) == 'X')
                kprinthex(k1);
            break;
        default:
            vidmem[(y * 80 + x) * 2] = *c;
            ++x;
            break;
        }

        if (x >= 80)
        {
            ++y;
            x = 0;
        }

        ++c;
    }
}

void kcls()
{
    // assume 80x25
    unsigned char *vidmem = (unsigned char *) VIDEO_MEMORY_ADDR;
    for (; vidmem < ((unsigned char *) VIDEO_MEMORY_ADDR + 80*25*2); vidmem += 2)
    {
        *vidmem = ' ';
        *(vidmem + 1) = 0x07;
    }

    x = 0; 
    y = 0;
}