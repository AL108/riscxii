#include <stdint.h>

void dump_word(int32_t sint)
{
    int32_t dw_vr_addr = 0x828;
    asm volatile("sw %[sint], 0(%[dw_vr_addr])"
                 :
                 : [sint] "r"(sint), [dw_vr_addr] "r"(dw_vr_addr));
}

int main()
{
    dump_word(100000);
    return 0;
}