#ifndef __KSTDIO_HEADER__
#define __KSTDIO_HEADER__

#include "kstdlib.h"


#define VIDEO_ADDR              0xB8000
#define VIDEO_COLS              80
#define VIDEO_ROWS              25

#define VIDEO_DEFAULT_SCROLL    1
#define VIDEO_DEFAULT_TAB_SIZE  4


void kprintf(const char *str, ...);
void kcls();
void ksetcur(int kx, int ky);
int kgetcurx();
int kgetcury();


#endif // __KSTDIO_HEADER__
