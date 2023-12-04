#include <stdint.h>

void dump_registers()
{
    int32_t dr_vr_addr = 0x0824;
    int rs2 = 0;
    asm volatile("sb %[rs2], 0(%[dr_vr_addr])"
                 :
                 : [rs2] "r"(rs2), [dr_vr_addr] "r"(dr_vr_addr));
}

int main()
{
    dump_registers();
    return 0;
}