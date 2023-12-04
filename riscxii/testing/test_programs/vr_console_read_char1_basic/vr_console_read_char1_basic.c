#include <stdint.h>

inline int32_t get_char()
{
    int32_t c;
    int32_t read_char_vr_addr = 0x0812;
    asm volatile("lb %[c], 0(%[read_char_vr_addr])"
                 : [c] "=r"(c)
                 : [read_char_vr_addr] "r"(read_char_vr_addr));
    return c;
}

void print_char(char c)
{
    int32_t write_char_vr_addr = 0x800;
    asm volatile("sb %[c], 0(%[write_char_vr_addr])"
                 :
                 : [c] "r"(c), [write_char_vr_addr] "r"(write_char_vr_addr));
}

int main()
{
    print_char(get_char());
    return 0;
}