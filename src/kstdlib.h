#ifndef __KSTDLIB_HEADER__
#define __KSTDLIB_HEADER__

int kstrlen(const char *str);
unsigned char * kmemcpy(const unsigned char *src, unsigned char *dest, int nbytes);
void kmemset(unsigned char *dest, unsigned char value, int nbytes);
char *itoa(int num, char *dest, int base);

#endif // __KSTDLIB_HEADER__
