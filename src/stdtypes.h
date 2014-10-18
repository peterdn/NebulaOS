#ifndef __STDTYPES_HEADER__
#define __STDTYPES_HEADER__

#ifdef __i386__

#define uint8_t     unsigned char
#define uint16_t    unsigned short
#define uint32_t    unsigned int
#define uint64_t    unsigned long long

#elif __x86_64__

#define uint8_t     unsigned char
#define uint16_t    unsigned short
#define uint32_t    unsigned int
#define uint64_t    unsigned long

#else
#error "Unsupported architecture or compiler!"
#endif

#endif // __STDTYPES_HEADER__
