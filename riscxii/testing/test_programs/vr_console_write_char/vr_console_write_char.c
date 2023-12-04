#include <stdint.h>

void print_char(char c)
{
    int32_t write_char_vr_addr = 0x800;
    asm volatile("sb %[c], 0(%[write_char_vr_addr])"
                 :
                 : [c] "r"(c), [write_char_vr_addr] "r"(write_char_vr_addr));
}

int main()
{
    print_char('A');
    return 0;
}