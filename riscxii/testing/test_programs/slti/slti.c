#include <stdint.h>

void print_sint(int sint)
{
    int32_t write_sint_vr_addr = 0x0804;
    asm volatile("sh %[sint], 0(%[write_sint_vr_addr])"
                 :
                 : [sint] "r"(sint), [write_sint_vr_addr] "r"(write_sint_vr_addr));
}

inline int32_t slti_test(int32_t val1)
{
    int32_t res;
    asm volatile("slt %[res], %[val1], 1"
                 : [res] "=r"(res)
                 : [val1] "r"(val1));
    return res;
}

int main()
{
    int32_t res = slti_test(0);
    print_sint(res);
    return 0;
}