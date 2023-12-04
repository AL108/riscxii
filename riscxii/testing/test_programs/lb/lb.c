#include <stdint.h>

void print_sint(int32_t sint)
{
    int32_t write_sint_vr_addr = 0x0804;
    asm volatile("sb %[sint], 0(%[write_sint_vr_addr])"
                 :
                 : [sint] "r"(sint), [write_sint_vr_addr] "r"(write_sint_vr_addr));
}

inline int32_t get_sint()
{
    int32_t sint;
    int32_t read_sint_vr_addr = 0x0816;
    asm volatile("lb %[sint], 0(%[read_sint_vr_addr])"
                 : [sint] "=r"(sint)
                 : [read_sint_vr_addr] "r"(read_sint_vr_addr));

    return sint;
}

int main()
{
    print_sint(get_sint());
    print_sint(get_sint());
    print_sint(get_sint());
    print_sint(get_sint());
    print_sint(get_sint());
    return 0;
}