int main()
{
    int request_size = 120;
    register int region_addr asm("t3");
    *((int *)0x0834) = region_addr; // free the two blocks
    return 0;
}