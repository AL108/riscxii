#ifndef PROG_INST_H
#define PROG_INST_H

#ifndef LOCAL_HEADERS
#define LOCAL_HEADERS
#include "./../header_files/loc_headers.h"
#endif

// INSTRUCTION HANDLER FUNCTION SIGNATURES FOR PROGRAM FLOW INSTRUCTIONS

bool slt(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2);
bool slti(vm_state *vm, int8_t rd, int8_t rs1, int32_t imm);
bool sltu(vm_state *vm, int8_t rd, int8_t rs1, int8_t rs2);
bool sltiu(vm_state *vm, int8_t rd, int8_t rs1, int32_t imm);
bool beq(vm_state *vm, int8_t rs1, int8_t rs2, int32_t imm);
bool bne(vm_state *vm, int8_t rs1, int8_t rs2, int32_t imm);
bool blt(vm_state *vm, int8_t rs1, int8_t rs2, int32_t imm);
bool bltu(vm_state *vm, int8_t rs1, int8_t rs2, int32_t imm);
bool bge(vm_state *vm, int8_t rs1, int8_t rs2, int32_t imm);
bool bgeu(vm_state *vm, int8_t rs1, int8_t rs2, int32_t imm);
bool jal(vm_state *vm, int8_t rd, int32_t imm);
bool jalr(vm_state *vm, int8_t rd, int8_t rs1, int32_t imm);

#endif