
#ifndef LOCAL_HEADERS
#define LOCAL_HEADERS
#include "./../header_files/loc_headers.h"
#endif

#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        perror("Bad cmd args. Quitting...\n");
        return 1;
    }
    run_prog_ret ret = run_prog(argv[1]);
    switch (ret)
    {
    case RPR_FAILED_MI_LOAD:
        perror("Image load failed.\n");
        return 1;
        break;
    case RPR_SUCCESS:
        return 0;
        break;
    };
}