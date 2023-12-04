#ifndef LOCAL_HEADERS
#define LOCAL_HEADERS
#include "./../header_files/loc_headers.h"
#endif

load_ret load(vm_state *vm, int8_t rd, int8_t rs1, int16_t imm,
              mem_unit size, bool signed_)
{
    // the following ensures that the zero register is always zero
    if (rd == 0)
    {
        return LR_LOAD_SUCCESS;
    }

    int32_t mem_addr = vm->R[rs1] + imm;

    if (!signed_)
    {
        uint32_t loadval;
        uint32_t b1;
        uint32_t b2;
        uint32_t b3;
        uint32_t b4;
        switch (size)
        {
        case (BYTE):
            if (!valid_mem_addr(mem_addr))
            {
                return LR_ILLEGAL;
            }
            loadval = vm->M[mem_addr];
            break;
        case (HALFWORD):
            if (!valid_mem_addr(mem_addr) || !valid_mem_addr(mem_addr + 1))
            {
                return LR_ILLEGAL;
            }
            b1 = vm->M[mem_addr];
            b2 = vm->M[mem_addr + 1];
            loadval = COMBINE_BYTES(b1, b2, 0, 0);
            break;
        case (WORD):
            if (!valid_mem_addr(mem_addr) || !valid_mem_addr(mem_addr + 1) ||
                !valid_mem_addr(mem_addr + 2) || !valid_mem_addr(mem_addr + 3))
            {
                return LR_ILLEGAL;
            }
            b1 = vm->M[mem_addr];
            b2 = vm->M[mem_addr + 1];
            b3 = vm->M[mem_addr + 2];
            b4 = vm->M[mem_addr + 3];
            loadval = COMBINE_BYTES(b1, b2, b3, b4);
            break;
        }
        vm->R[rd] = loadval;
    }
    else
    {
        int32_t loadval;
        int32_t b1;
        int32_t b2;
        int32_t b3;
        int32_t b4;
        switch (size)
        {
        case (BYTE):
            if (!valid_mem_addr(mem_addr))
            {
                return LR_ILLEGAL;
            }
            loadval = SEXT((vm->M[mem_addr]), 8);
            break;
        case (HALFWORD):
            if (!valid_mem_addr(mem_addr) || !valid_mem_addr(mem_addr + 1))
            {
                return LR_ILLEGAL;
            }
            b1 = vm->M[mem_addr];
            b2 = vm->M[mem_addr + 1];
            loadval = SEXT(((b2 << 8) | b1), 16);
            break;
        case (WORD):
            if (!valid_mem_addr(mem_addr) || !valid_mem_addr(mem_addr + 1) ||
                !valid_mem_addr(mem_addr + 2) || !valid_mem_addr(mem_addr + 3))
            {
                return LR_ILLEGAL;
            }
            b1 = vm->M[mem_addr];
            b2 = vm->M[mem_addr + 1];
            b3 = vm->M[mem_addr + 2];
            b4 = vm->M[mem_addr + 3];
            loadval = COMBINE_BYTES(b1, b2, b3, b4);
            break;
        }
        vm->R[rd] = loadval;
    }

    vr_handler_return vr_ret = vr_handler(mem_addr, rd, vm, size);
    switch (vr_ret)
    {
    case (VR_INVALID_MEM_ADDR):
        return LR_LOAD_SUCCESS;
    case (VR_SUCCESS):
        return LR_LOAD_SUCCESS;
    case (VR_FAILURE):
        return LR_ILLEGAL;
    case (VR_FAILURE_MALLOC):
        return LR_ILLEGAL;
    default:
        return LR_LOAD_SUCCESS;
    }
}

store_ret store(vm_state *vm, int8_t rs1, int8_t rs2, int16_t imm,
                mem_unit size)
{
    int32_t mem_addr = vm->R[rs1] + imm;
    int32_t register_val = vm->R[rs2];
    int8_t b1 = EXTRACT_WBYTE1(register_val);
    int8_t b2 = EXTRACT_WBYTE2(register_val);
    int8_t b3 = EXTRACT_WBYTE3(register_val);
    int8_t b4 = EXTRACT_WBYTE4(register_val);
    switch (size)
    {
    case (BYTE):
        if (!valid_mem_addr(mem_addr))
        {
            return SR_ILLEGAL;
        }
        vm->M[mem_addr] = b1;
        break;
    case (HALFWORD):
        if (!valid_mem_addr(mem_addr) || !valid_mem_addr(mem_addr + 1))
        {
            return SR_ILLEGAL;
        }
        vm->M[mem_addr] = b1;
        vm->M[mem_addr + 1] = b2;
        break;
    case (WORD):
        if (!valid_mem_addr(mem_addr) || !valid_mem_addr(mem_addr + 1) ||
            !valid_mem_addr(mem_addr + 2) || !valid_mem_addr(mem_addr + 3))
        {
            return SR_ILLEGAL;
        }
        vm->M[mem_addr] = b1;
        vm->M[mem_addr + 1] = b2;
        vm->M[mem_addr + 2] = b3;
        vm->M[mem_addr + 3] = b4;
        break;
    }
    // 0 is to vr_handler to represent that this parameter is not used.
    vr_handler_return vr_ret = vr_handler(mem_addr, 0, vm, size);
    switch (vr_ret)
    {
    case (VR_INVALID_MEM_ADDR):
        return SR_STORE_SUCCESS;
    case (VR_HALT_REQUESTED):
        return SR_HALT_REQUESTED;
    case (VR_SUCCESS):
        return SR_STORE_SUCCESS;
    case (VR_FAILURE):
        return SR_ILLEGAL;
    case (VR_FAILURE_MALLOC):
        return SR_ILLEGAL;
    default:
        return SR_STORE_SUCCESS;
    }
}
