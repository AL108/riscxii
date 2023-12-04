#include <stdint.h>

void print_sint(int sint)
{
    int32_t write_sint_vr_addr = 0x0804;
    asm volatile("sh %[sint], 0(%[write_sint_vr_addr])"
                 :
                 : [sint] "r"(sint), [write_sint_vr_addr] "r"(write_sint_vr_addr));
}

int32_t bltu_test(uint32_t num1, uint32_t num2)
{
    if (num1 < num2)
    {
        print_sint(1);
    }
}

int main()
{
    bltu_test(0, 1);
    return 0;
}