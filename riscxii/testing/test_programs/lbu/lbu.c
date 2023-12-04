#include <stdint.h>

void print_uint(int32_t sint)
{
    int32_t write_uint_vr_addr = 0x0808;
    asm volatile("sb %[uint], 0(%[write_uint_vr_addr])"
                 :
                 : [uint] "r"(sint), [write_uint_vr_addr] "r"(write_uint_vr_addr));
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
    print_uint(get_sint());
    return 0;
}