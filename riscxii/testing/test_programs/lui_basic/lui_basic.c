#include <stdint.h>

void print_sint(int sint)
{
    int32_t write_sint_vr_addr = 0x0804;
    asm volatile("sw %[sint], 0(%[write_sint_vr_addr])"
                 :
                 : [sint] "r"(sint), [write_sint_vr_addr] "r"(write_sint_vr_addr));
}

int main()
{
    int32_t res = 2 << 12;
    print_sint(res);
    return 0;
}