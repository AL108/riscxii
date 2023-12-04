#include <stdint.h>

void print_uint(int32_t uint)
{
    int32_t write_uint_vr_addr = 0x0808;
    asm volatile("sw %[uint], 0(%[write_uint_vr_addr])"
                 :
                 : [uint] "r"(uint), [write_uint_vr_addr] "r"(write_uint_vr_addr));
}

int main()
{
    print_uint(1);
    return 0;
}