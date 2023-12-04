#include <stdint.h>

void print_sint(int sint)
{
    int32_t write_sint_vr_addr = 0x0804;
    asm volatile("sh %[sint], 0(%[write_sint_vr_addr])"
                 :
                 : [sint] "r"(sint), [write_sint_vr_addr] "r"(write_sint_vr_addr));
}

int32_t jalr_test()
{
    print_sint(1);
}

int main()
{
    void (*func_ptr)() = jalr_test; // Create a function pointer
    func_ptr();
    return 0;
}