#include <stdint.h>

void print_sint(int32_t sint)
{
    int32_t write_sint_vr_addr = 0x0804;
    asm volatile("sw %[sint], 0(%[write_sint_vr_addr])"
                 :
                 : [sint] "r"(sint), [write_sint_vr_addr] "r"(write_sint_vr_addr));
}

int main()
{
    print_sint(1);
    return 0;
}