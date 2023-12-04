#ifndef LOCAL_HEADERS
#define LOCAL_HEADERS
#include "./../header_files/loc_headers.h"
#endif

#include <stdbool.h>

bool add(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2)
{
    // the following ensures that the zero register is always zero
    if (rd == 0)
    {
        return true;
    }
    vm->R[rd] = vm->R[rs1] + vm->R[rs2];
    return true;
}

bool addi(vm_state *vm, int8_t rd, int8_t rs1, int32_t imm)
{
    // the following ensures that the zero register is always zero
    if (rd == 0)
    {
        return true;
    }
    vm->R[rd] = vm->R[rs1] + imm;
    return true;
}

bool sub(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2)
{
    // the following ensures that the zero register is always zero
    if (rd == 0)
    {
        return true;
    }
    vm->R[rd] = vm->R[rs1] - vm->R[rs2];
    return true;
}

bool lui(vm_state *vm, int8_t rd, int32_t imm)
{
    // the following ensures that the zero register is always zero
    if (rd == 0)
    {
        return true;
    }
    int8_t lower_register_size = 12;
    vm->R[rd] = imm << lower_register_size;
    return true;
}

bool xor_(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2)
{
    // the following ensures that the zero register is always zero
    if (rd == 0)
    {
        return true;
    }
    vm->R[rd] = vm->R[rs1] ^ vm->R[rs2];
    return true;
}

bool xori(vm_state *vm, int8_t rd, int8_t rs1, int32_t imm)
{
    // the following ensures that the zero register is always zero
    if (rd == 0)
    {
        return true;
    }
    vm->R[rd] = vm->R[rs1] ^ imm;
    return true;
}

bool or_(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2)
{
    // the following ensures that the zero register is always zero
    if (rd == 0)
    {
        return true;
    }
    vm->R[rd] = vm->R[rs1] | vm->R[rs2];
    return true;
}

bool ori(vm_state *vm, int8_t rd, int8_t rs1, int32_t imm)
{
    // the following ensures that the zero register is always zero
    if (rd == 0)
    {
        return true;
    }
    vm->R[rd] = vm->R[rs1] | imm;
    return true;
}

bool and_(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2)
{
    // the following ensures that the zero register is always zero
    if (rd == 0)
    {
        return true;
    }
    vm->R[rd] = vm->R[rs1] & vm->R[rs2];
    return true;
}

bool andi(vm_state *vm, int8_t rd, int8_t rs1, int32_t imm)
{
    // the following ensures that the zero register is always zero
    if (rd == 0)
    {
        return true;
    }
    vm->R[rd] = vm->R[rs1] & imm;
    return true;
}

bool sll(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2)
{
    // the following ensures that the zero register is always zero
    if (rd == 0)
    {
        return true;
    }
    vm->R[rd] = vm->R[rs1] << vm->R[rs2];
    return true;
}

bool srl(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2)
{
    // the following ensures that the zero register is always zero
    if (rd == 0)
    {
        return true;
    }
    // cast to make shift logical, not arithmetic
    vm->R[rd] = (uint32_t)vm->R[rs1] >> (uint32_t)vm->R[rs2];
    return true;
}

bool sra(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2)
{
    // the following ensures that the zero register is always zero
    if (rd == 0)
    {
        return true;
    }
    vm->R[rd] = vm->R[rs1] >> vm->R[rs2];
    return true;
}