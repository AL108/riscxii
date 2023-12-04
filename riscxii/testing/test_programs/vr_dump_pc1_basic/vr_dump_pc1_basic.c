#include <stdint.h>

void dump_pc()
{
    int32_t dp_vr_addr = 0x0820;
    int zero = 0;
    asm volatile("sb %[zero], 0(%[dpc_vr_addr])"
                 :
                 : [zero] "r"(zero), [dpc_vr_addr] "r"(dp_vr_addr));
}

int main()
{
    dump_pc();
    return 0;
}