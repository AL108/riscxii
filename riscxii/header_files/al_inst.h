#ifndef AL_INST_H
#define AL_INST_H

#ifndef LOCAL_HEADERS
#define LOCAL_HEADERS
#include "./../header_files/loc_headers.h"
#endif

#include <stdbool.h>

// INSTRUCTION HANDLER FUNCTION SIGNATURES FOR ARITHMETIC AND LOGIC INSTRUCTIONS

bool add(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2);
bool addi(vm_state *vm, int8_t rd, int8_t rs1, int32_t imm);
bool sub(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2);
bool lui(vm_state *vm, int8_t rd, int32_t imm);
bool xor_(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2);
bool xori(vm_state *vm, int8_t rd, int8_t rs1, int32_t imm);
bool or_(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2);
bool ori(vm_state *vm, int8_t rd, int8_t rs1, int32_t imm);
bool and_(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2);
bool andi(vm_state *vm, int8_t rd, int8_t rs1, int32_t imm);
bool sll(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2);
bool srl(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2);
bool sra(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2);

#endif