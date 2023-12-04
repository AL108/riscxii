#ifndef LOCAL_HEADERS
#define LOCAL_HEADERS
#include "./../header_files/loc_headers.h"
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// returns true if the memory address represents
// a virtual routine
vr_handler_return
vr_handler(int32_t vr_addr, int8_t rd, vm_state *vm, mem_unit size)
{
    vr_handler_return return_val = VR_SUCCESS;

    switch (vr_addr)
    {
    case (VR_CONSOLE_WRITE_CHAR):
        printf("%c", vm->M[VR_CONSOLE_WRITE_CHAR]);
        fflush(stdout);
        break;
    case (VR_CONSOLE_WRITE_SIGNED_INT):
    {
        int32_t val;
        switch (size)
        {
        case (BYTE):
            val = SEXT(vm->M[VR_CONSOLE_WRITE_SIGNED_INT], 8);
            break;
        case (HALFWORD):
        {
            val = SEXT(COMBINE_BYTES(vm->M[VR_CONSOLE_WRITE_SIGNED_INT],
                                     vm->M[VR_CONSOLE_WRITE_SIGNED_INT + 1],
                                     0, 0),
                       16);
        }
        break;
        case (WORD):
        {
            val = COMBINE_BYTES(vm->M[VR_CONSOLE_WRITE_SIGNED_INT],
                                vm->M[VR_CONSOLE_WRITE_SIGNED_INT + 1],
                                vm->M[VR_CONSOLE_WRITE_SIGNED_INT + 2],
                                vm->M[VR_CONSOLE_WRITE_SIGNED_INT + 3]);
        }
        }
        printf("%d", val);
    }
        fflush(stdout);
        break;
    case (VR_CONSOLE_WRITE_UNSIGNED_INT):
    {
        uint32_t val;
        switch (size)
        {
        case (BYTE):
            val = vm->M[VR_CONSOLE_WRITE_UNSIGNED_INT];
            break;
        case (HALFWORD):
        {
            val = COMBINE_BYTES(vm->M[VR_CONSOLE_WRITE_UNSIGNED_INT],
                                vm->M[VR_CONSOLE_WRITE_UNSIGNED_INT + 1],
                                0, 0);
        }
        break;
        case (WORD):
        {
            val = COMBINE_BYTES(vm->M[VR_CONSOLE_WRITE_UNSIGNED_INT],
                                vm->M[VR_CONSOLE_WRITE_UNSIGNED_INT + 1],
                                vm->M[VR_CONSOLE_WRITE_UNSIGNED_INT + 2],
                                vm->M[VR_CONSOLE_WRITE_UNSIGNED_INT + 3]);
        }
        }
        printf("%x", val);
        fflush(stdout);
        break;
    }
    case (VR_HALT):
        return_val = VR_HALT_REQUESTED;
        break;
    case (VR_CONSOLE_READ_CHAR):
        if (rd != 0)
        {
            vm->R[rd] = getc(stdin);
        }
        return_val = VR_SUCCESS;
        break;
    case (VR_READ_SIGNED_INT):
        if (rd != 0)
        {
            scanf("%d", &(vm->R[rd]));
        }
        break;
    case (VR_CONSOLE_DUMP_PC):
        printf("%08x", vm->pc);
        fflush(stdout);
        return_val = VR_SUCCESS;
        break;
    case (VR_CONSOLE_DUMP_REGISTERS):
        register_dump(vm);
        return_val = VR_SUCCESS;
        break;
    case (VR_CONSOLE_DUMP_MEMORY_WORD):
    {
        int32_t val = COMBINE_BYTES(vm->M[VR_CONSOLE_DUMP_MEMORY_WORD],
                                    vm->M[VR_CONSOLE_DUMP_MEMORY_WORD + 1],
                                    vm->M[VR_CONSOLE_DUMP_MEMORY_WORD + 2],
                                    vm->M[VR_CONSOLE_DUMP_MEMORY_WORD + 3]);
        printf("%08x", val);
    }
        fflush(stdout);
        return_val = VR_SUCCESS;
        break;
    case (VR_MALLOC):
    {
        int32_t val;
        switch (size)
        {
        case (BYTE):
            val = SEXT(vm->M[VR_MALLOC], 8);
            break;
        case (HALFWORD):
        {
            val = SEXT(COMBINE_BYTES(vm->M[VR_MALLOC],
                                     vm->M[VR_MALLOC + 1],
                                     0, 0),
                       16);
        }
        break;
        case (WORD):
        {
            val = COMBINE_BYTES(vm->M[VR_MALLOC],
                                vm->M[VR_MALLOC + 1],
                                vm->M[VR_MALLOC + 2],
                                vm->M[VR_MALLOC + 3]);
        }
        }
        if (malloc_(vm, val))
        {
            return_val = VR_SUCCESS;
        }
        else
        {
            return_val = VR_FAILURE_MALLOC;
        }
    }
    break;
    case (VR_FREE):
    {
        int32_t val;
        switch (size)
        {
        case (BYTE):
            val = SEXT(vm->M[VR_FREE], 8);
            break;
        case (HALFWORD):
        {
            val = SEXT(COMBINE_BYTES(vm->M[VR_FREE],
                                     vm->M[VR_FREE + 1],
                                     0, 0),
                       16);
        }
        break;
        case (WORD):
        {
            val = COMBINE_BYTES(vm->M[VR_FREE],
                                vm->M[VR_FREE + 1],
                                vm->M[VR_FREE + 2],
                                vm->M[VR_FREE + 3]);
        }
        }
        if (free_(vm, val))
        {
            return_val = VR_SUCCESS;
        }
        else
        {
            return_val = VR_FAILURE;
        }
    }
    break;
    default:
        return_val = VR_INVALID_MEM_ADDR;
    }
    return return_val;
}