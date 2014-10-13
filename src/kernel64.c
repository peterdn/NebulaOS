

void kernel_main64()
{
    *((char*)0xB8000) = '6';

    for(;;);
}