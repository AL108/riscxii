#ifndef LOCAL_HEADERS
#define LOCAL_HEADERS
#include "./../header_files/loc_headers.h"
#endif

bool slt(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2)
{
    if (rd == 0)
    {
        return true;
    }
    vm->R[rd] = (vm->R[rs1] < vm->R[rs2]) ? 1 : 0;
    return true;
}

bool slti(vm_state *vm, int8_t rd, int8_t rs1, int32_t imm)
{
    if (rd == 0)
    {
        return true;
    }
    vm->R[rd] = (vm->R[rs1] < imm) ? 1 : 0;
    return true;
}

bool sltu(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2)
{
    if (rd == 0)
    {
        return true;
    }
    vm->R[rd] = ((uint32_t)vm->R[rs1] < (uint32_t)vm->R[rs2]) ? 1 : 0;
    return true;
}

bool sltiu(vm_state *vm, int8_t rd, int8_t rs1, int32_t imm)
{
    if (rd == 0)
    {
        return true;
    }
    vm->R[rd] = ((uint32_t)vm->R[rs1] < (uint32_t)imm) ? 1 : 0;
    return true;
}

// returns true if branches, false if not
bool beq(vm_state *vm, int8_t rs1, int8_t rs2, int32_t imm)
{
    if (vm->R[rs1] == vm->R[rs2])
    {
        vm->pc += (imm << 1);
        return true;
    }
    return false;
}

// returns true if branches, false if not
bool bne(vm_state *vm, int8_t rs1, int8_t rs2, int32_t imm)
{
    if (vm->R[rs1] != vm->R[rs2])
    {
        vm->pc += (imm << 1);
        return true;
    }
    return false;
}

// returns true if branches, false if not
bool blt(vm_state *vm, int8_t rs1, int8_t rs2, int32_t imm)
{
    if (vm->R[rs1] < vm->R[rs2])
    {
        vm->pc += (imm << 1);
        return true;
    }
    return false;
}

// returns true if branches, false if not
bool bltu(vm_state *vm, int8_t rs1, int8_t rs2, int32_t imm)
{
    if ((uint32_t)vm->R[rs1] < (uint32_t)vm->R[rs2])
    {
        vm->pc += (imm << 1);
        return true;
    }
    return false;
}

// returns true if branches, false if not
bool bge(vm_state *vm, int8_t rs1, int8_t rs2, int32_t imm)
{
    if (vm->R[rs1] >= vm->R[rs2])
    {
        vm->pc += (imm << 1);
        return true;
    }
    return false;
}

// returns true if branches, false if not
bool bgeu(vm_state *vm, int8_t rs1, int8_t rs2, int32_t imm)
{
    if ((uint32_t)vm->R[rs1] >= (uint32_t)vm->R[rs2])
    {
        vm->pc += (imm << 1);
        return true;
    }
    return false;
}

bool jal(vm_state *vm, int8_t rd, int32_t imm)
{
    // the following ensures that the zero register is always zero
    if (rd != 0)
    {
        vm->R[rd] = vm->pc + INST_SZ;
    }
    vm->pc += imm << 1;
    return true;
}

bool jalr(vm_state *vm, int8_t rd, int8_t rs1, int32_t imm)
{
    if (rd != 0)
    {
        vm->R[rd] = vm->pc + INST_SZ;
    }
    vm->pc = vm->R[rs1] + imm;
    return true;
}