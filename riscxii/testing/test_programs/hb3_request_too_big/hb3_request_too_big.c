#include <stdint.h>

int main()
{
    int32_t hb_region_sz = 8192;
    register int region_addr asm("t3");
    *((int *)0x0830) = hb_region_sz + 1; // malloc_
    return 0;
}