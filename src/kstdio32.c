
#define VIDEO_MEMORY_ADDR 0xB8000

int x;
int y;


void k32printf(char *str, ...);

int k32strlen(char *str)
{
    int i = 0;
    while (str[i] != '\0')
        ++i;
    return i;
}

void k32printhex(int hexnum)
{
    char buffer[16] = "";
    char rbuffer[16] = "";

    int i = 0;
    do
    {
        int r = hexnum % 0x10;
        buffer[i++] = (char) (r < 10 ? r + 0x30 : (r-10) + 0x41);
        hexnum = hexnum / 0x10; 
    }
    while (hexnum > 0);

    char *b = buffer + k32strlen(buffer);
    char *r = rbuffer;
    while (b-- != buffer)
    {
        *r++ = *b;
    }

    k32printf(rbuffer);
}


void k32printf(char *str, ...)
{
    unsigned char *vidmem = (unsigned char *) VIDEO_MEMORY_ADDR;
    char *c = str;

    char ** arg = (char **) &str;
    arg++;

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
                k32printhex(*((int *)arg++));
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

void k32cls()
{
    // assume 80x25
    unsigned char *vidmem = (unsigned char *) VIDEO_MEMORY_ADDR;
    for (; vidmem < ((unsigned char *) VIDEO_MEMORY_ADDR + 80*25*2); vidmem += 2)
    {
        *vidmem = ' ';
        *(vidmem + 1) = 0x0F;
    }

    x = 0; 
    y = 0;
}