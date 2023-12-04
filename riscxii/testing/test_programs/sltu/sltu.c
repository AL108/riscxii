#include <stdint.h>

void print_sint(int sint)
{
    int32_t write_sint_vr_addr = 0x0804;
    asm volatile("sh %[sint], 0(%[write_sint_vr_addr])"
                 :
                 : [sint] "r"(sint), [write_sint_vr_addr] "r"(write_sint_vr_addr));
}

inline int32_t sltu_test(int32_t val1, int32_t val2)
{
    int32_t res;
    asm volatile("sltu %[res], %[val1], %[val2]"
                 : [res] "=r"(res)
                 : [val1] "r"(val1), [val2] "r"(val2));
    return res;
}

int main()
{
    int32_t res = sltu_test(0, 1);
    print_sint(res);
    return 0;
}