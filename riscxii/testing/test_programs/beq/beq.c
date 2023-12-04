#include <stdint.h>

void print_sint(int sint)
{
    int32_t write_sint_vr_addr = 0x0804;
    asm volatile("sh %[sint], 0(%[write_sint_vr_addr])"
                 :
                 : [sint] "r"(sint), [write_sint_vr_addr] "r"(write_sint_vr_addr));
}

int32_t beq_test(int32_t num1, int32_t num2)
{
    if (num1 == num2)
    {
        print_sint(1);
    }
    else
    {
        print_sint(0);
    }
}

int main()
{
    beq_test(1, 1);
    return 0;
}