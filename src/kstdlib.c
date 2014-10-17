#include "kstdlib.h"

int kstrlen(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
        ++i;
    return i;
}
