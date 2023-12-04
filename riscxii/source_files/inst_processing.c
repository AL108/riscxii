#ifndef LOCAL_HEADERS
#define LOCAL_HEADERS
#include "./../header_files/loc_headers.h"
#endif

run_inst_ret run_instruction(vm_state *vm)
{
    if (!valid_mem_addr(vm->pc) || !valid_mem_addr(vm->pc + 3))
    {
        return RIR_ILLEGAL_OP;
    }
    uint32_t cur_inst = vm->M[vm->pc] |
                        (vm->M[vm->pc + 1] << 8) |
                        (vm->M[vm->pc + 2] << 16) |
                        (vm->M[vm->pc + 3] << 24);
    // printf("cur inst: %08x\n", cur_inst);
    // fflush(stdout);
    int8_t opcode = EXTRACT_OPCODE(cur_inst);
    int8_t func7 = 0;
    int8_t func3 = 0;
    run_inst_ret return_val = RIR_PC_UNSET;
    switch (opcode)
    {
    case (OPCODE_0110011):
        // All instructions with opcode 0110011
        // have func3 and func7 fields, so we
        // can combine these fields.
        func3 = EXTRACT_FUNC3(cur_inst);
        func7 = EXTRACT_FUNC7(cur_inst);
        int f3_f7_joined = func3 | (func7 << 3);
        switch (f3_f7_joined)
        {
        case (FUNC3_ADD | (FUNC7_ADD << 3)):
            add(vm, EXTRACT_RD(cur_inst),
                EXTRACT_RS1(cur_inst),
                EXTRACT_RS2(cur_inst));
            break;
        case (FUNC3_SUB | (FUNC7_SUB << 3)):
            sub(vm, EXTRACT_RD(cur_inst),
                EXTRACT_RS1(cur_inst),
                EXTRACT_RS2(cur_inst));
            break;
        case (FUNC3_XOR | (FUNC7_XOR << 3)):
            xor_(vm, EXTRACT_RD(cur_inst),
                 EXTRACT_RS1(cur_inst),
                 EXTRACT_RS2(cur_inst));
            break;
        case (FUNC3_OR | (FUNC7_OR << 3)):
            or_(vm, EXTRACT_RD(cur_inst),
                EXTRACT_RS1(cur_inst),
                EXTRACT_RS2(cur_inst));
            break;
        case (FUNC3_AND | (FUNC7_AND << 3)):
            and_(vm, EXTRACT_RD(cur_inst),
                 EXTRACT_RS1(cur_inst),
                 EXTRACT_RS2(cur_inst));
            break;
        case (FUNC3_SLL | (FUNC7_SLL << 3)):
            sll(vm, EXTRACT_RD(cur_inst),
                EXTRACT_RS1(cur_inst),
                EXTRACT_RS2(cur_inst));
            break;
        case (FUNC3_SRL | (FUNC7_SRL << 3)):
            srl(vm, EXTRACT_RD(cur_inst),
                EXTRACT_RS1(cur_inst),
                EXTRACT_RS2(cur_inst));
            break;
        case (FUNC3_SRA | (FUNC7_SRA << 3)):
            sra(vm, EXTRACT_RD(cur_inst),
                EXTRACT_RS1(cur_inst),
                EXTRACT_RS2(cur_inst));
            break;
        case (FUNC3_SLT | (FUNC7_SLT << 3)):
            slt(vm, EXTRACT_RD(cur_inst),
                EXTRACT_RS1(cur_inst),
                EXTRACT_RS2(cur_inst));
            break;
        case (FUNC3_SLTU | (FUNC7_SLTU << 3)):
            sltu(vm, EXTRACT_RD(cur_inst),
                 EXTRACT_RS1(cur_inst),
                 EXTRACT_RS2(cur_inst));
            break;
        default:
            return_val = RIR_INST_UNIMPLEMENTED;
        }
        break;
    case (OPCODE_0010011):
        // All instructions with this opcode
        // have a func3 field, and don't have a func7 field.
        func3 = EXTRACT_FUNC3(cur_inst);
        switch (func3)
        {
        case (FUNC3_ADDI):
            addi(vm, EXTRACT_RD(cur_inst),
                 EXTRACT_RS1(cur_inst),
                 SEXT(EXTRACT_IMM_I(cur_inst), IMM_SZ_I));
            break;
        case (FUNC3_XORI):
            // 12 here is the imm size for type I instructions
            xori(vm, EXTRACT_RD(cur_inst),
                 EXTRACT_RS1(cur_inst),
                 SEXT(EXTRACT_IMM_I(cur_inst), IMM_SZ_I));
            break;
        case (FUNC3_ORI):
            // 12 here is the imm size for type I instructions
            ori(vm, EXTRACT_RD(cur_inst),
                EXTRACT_RS1(cur_inst),
                SEXT(EXTRACT_IMM_I(cur_inst), IMM_SZ_I));
            break;
        case (FUNC3_ANDI):
            // 12 here is the imm size for type I instructions
            andi(vm, EXTRACT_RD(cur_inst),
                 EXTRACT_RS1(cur_inst),
                 SEXT(EXTRACT_IMM_I(cur_inst), IMM_SZ_I));
            break;
        case (FUNC3_SLTI):
            // 12 here is the imm size for type I instructions
            slti(vm, EXTRACT_RD(cur_inst),
                 EXTRACT_RS1(cur_inst),
                 SEXT(EXTRACT_IMM_I(cur_inst), IMM_SZ_I));
            break;
        case (FUNC3_SLTIU):
            // 12 here is the imm size for type I instructions
            sltiu(vm, EXTRACT_RD(cur_inst),
                  EXTRACT_RS1(cur_inst),
                  SEXT(EXTRACT_IMM_I(cur_inst), IMM_SZ_I));
            break;
        default:
            return_val = RIR_INST_UNIMPLEMENTED;
        }
        break;
    case (OPCODE_0110111):
        // only one instruction has this opcode
        // 20 here is the imm size for lui
        lui(vm, EXTRACT_RD(cur_inst),
            EXTRACT_IMM_U(cur_inst));
        break;
    case (OPCODE_0000011):
        // instructions with this opcode have func3, but no
        // func7 field.
        func3 = EXTRACT_FUNC3(cur_inst);
        switch (func3)
        {
        case (FUNC3_LB):
            // 12 here is the imm size for type I instructions
            load(vm, EXTRACT_RD(cur_inst),
                 EXTRACT_RS1(cur_inst),
                 SEXT(EXTRACT_IMM_I(cur_inst), IMM_SZ_I), BYTE, true);
            break;
        case (FUNC3_LH):
            // 12 here is the imm size for type I instructions
            load(vm, EXTRACT_RD(cur_inst),
                 EXTRACT_RS1(cur_inst),
                 SEXT(EXTRACT_IMM_I(cur_inst), IMM_SZ_I), HALFWORD, true);
            break;
        case (FUNC3_LW):
            // 12 here is the imm size for type I instructions
            load(vm, EXTRACT_RD(cur_inst),
                 EXTRACT_RS1(cur_inst),
                 SEXT(EXTRACT_IMM_I(cur_inst), IMM_SZ_I), WORD, true);
            break;
        case (FUNC3_LBU):
            load(vm, EXTRACT_RD(cur_inst),
                 EXTRACT_RS1(cur_inst),
                 SEXT(EXTRACT_IMM_I(cur_inst), IMM_SZ_I), BYTE, false);
            break;
        case (FUNC3_LHU):
            // 12 here is the imm size for type I instructions
            load(vm, EXTRACT_RD(cur_inst),
                 EXTRACT_RS1(cur_inst),
                 SEXT(EXTRACT_IMM_I(cur_inst), IMM_SZ_I), HALFWORD, false);
            break;
        default:
            return_val = RIR_INST_UNIMPLEMENTED;
        }
        break;
    case (OPCODE_0100011):
        // instructions with this opcode have func3, but no
        // func7 field.
        func3 = EXTRACT_FUNC3(cur_inst);
        switch (func3)
        {
        case (FUNC3_SB):
            switch (store(vm, EXTRACT_RS1(cur_inst),
                          EXTRACT_RS2(cur_inst),
                          SEXT(EXTRACT_IMM_S(cur_inst), IMM_SZ_S), BYTE))
            {
            case SR_STORE_SUCCESS:
                break;
            case SR_HALT_REQUESTED:
                return_val = RIR_HALT_REQUESTED;
                break;
            case SR_ILLEGAL:
                return_val = RIR_ILLEGAL_OP;
            default:
                break;
            }
            break;
        case (FUNC3_SH):
            switch (store(vm, EXTRACT_RS1(cur_inst),
                          EXTRACT_RS2(cur_inst),
                          SEXT(EXTRACT_IMM_S(cur_inst), IMM_SZ_S), HALFWORD))
            {
            case SR_STORE_SUCCESS:
                break;
            case SR_HALT_REQUESTED:
                return_val = RIR_HALT_REQUESTED;
                break;
            case SR_ILLEGAL:
                return_val = RIR_ILLEGAL_OP;
                break;
            }
            break;
        case (FUNC3_SW):
            switch (store(vm, EXTRACT_RS1(cur_inst),
                          EXTRACT_RS2(cur_inst),
                          SEXT(EXTRACT_IMM_S(cur_inst), IMM_SZ_S), WORD))
            {
            case SR_STORE_SUCCESS:
                break;
            case SR_HALT_REQUESTED:
                return_val = RIR_HALT_REQUESTED;
                break;
            case SR_ILLEGAL:
                return_val = RIR_ILLEGAL_OP;
            default:
                break;
            }
            break;
        default:
            return_val = RIR_INST_UNIMPLEMENTED;
        }
        break;
    case (OPCODE_1100011):
        // instructions with this opcode have func3, but no
        // func7 field.
        func3 = EXTRACT_FUNC3(cur_inst);
        switch (func3)
        {
        case (FUNC3_BEQ):
            if (beq(vm, EXTRACT_RS1(cur_inst),
                    EXTRACT_RS2(cur_inst),
                    SEXT(EXTRACT_IMM_SB(cur_inst), IMM_SZ_SB)))
            {
                return_val = RIR_PC_SET;
            }
            break;
        case (FUNC3_BNE):
            if (bne(vm, EXTRACT_RS1(cur_inst),
                    EXTRACT_RS2(cur_inst),
                    SEXT(EXTRACT_IMM_SB(cur_inst), IMM_SZ_SB)))
            {
                return_val = RIR_PC_SET;
            }
            break;
        case (FUNC3_BLT):
            if (blt(vm, EXTRACT_RS1(cur_inst),
                    EXTRACT_RS2(cur_inst),
                    SEXT(EXTRACT_IMM_SB(cur_inst), IMM_SZ_SB)))
            {
                return_val = RIR_PC_SET;
            }
            break;
        case (FUNC3_BLTU):
            if (bltu(vm, EXTRACT_RS1(cur_inst),
                     EXTRACT_RS2(cur_inst),
                     SEXT(EXTRACT_IMM_SB(cur_inst), IMM_SZ_SB)))
            {
                return_val = RIR_PC_SET;
            }
            break;
        case (FUNC3_BGE):
            if (bge(vm, EXTRACT_RS1(cur_inst),
                    EXTRACT_RS2(cur_inst),
                    SEXT(EXTRACT_IMM_SB(cur_inst), IMM_SZ_SB)))
            {
                return_val = RIR_PC_SET;
            }
            break;
        case (FUNC3_BGEU):
            if (bgeu(vm, EXTRACT_RS1(cur_inst),
                     EXTRACT_RS2(cur_inst),
                     SEXT(EXTRACT_IMM_SB(cur_inst), IMM_SZ_SB)))
            {
                return_val = RIR_PC_SET;
            }
            break;
        default:
            return_val = RIR_INST_UNIMPLEMENTED;
        }
        break;
    case (OPCODE_1101111):
        jal(vm, EXTRACT_RD(cur_inst),
            SEXT(EXTRACT_IMM_UJ(cur_inst), IMM_SZ_UJ));
        return_val = RIR_PC_SET;
        break;
    case (OPCODE_1100111):
        // only one instruction has this opcode
        jalr(vm, EXTRACT_RD(cur_inst),
             EXTRACT_RS1(cur_inst),
             SEXT(EXTRACT_IMM_I(cur_inst), IMM_SZ_I));
        return_val = RIR_PC_SET;
        break;
    default:
        return_val = RIR_INST_UNIMPLEMENTED;
    }
    return return_val;
}

run_prog_ret run_prog(const char *filepath)
{
    vm_state vm;
    if (!init_vm(&vm, filepath))
    {
        return RPR_FAILED_MI_LOAD;
    }
    run_inst_ret cur_inst_return;
    while (vm.pc < INST_MEM_END_ADDR)
    {
        cur_inst_return = run_instruction(&vm);
        switch (cur_inst_return)
        {
        case RIR_PC_UNSET:
            vm.pc += INST_SZ;
            break;
        case RIR_PC_SET:
            break;
        case RIR_HALT_REQUESTED:
            printf("CPU Halt Requested\n");
            free_all_mallocs(&vm);
            return RPR_SUCCESS;
        case RIR_PROGRAM_COMPLETE:
            free_all_mallocs(&vm);
            return RPR_SUCCESS;
        case RIR_INST_UNIMPLEMENTED:
        {
            int32_t cur_inst = vm.M[vm.pc] | (vm.M[vm.pc + 1] << 8) |
                               (vm.M[vm.pc + 2] << 16) |
                               (vm.M[vm.pc + 3] << 24);
            printf("Instruction Not Implemented: 0x%08x\n", cur_inst);
            printf("PC = 0x%08x;\n", vm.pc);
            register_dump(&vm);
            free_all_mallocs(&vm);
        }
            return RPR_SUCCESS;
        case (RIR_ILLEGAL_OP):

        {
            uint32_t cur_inst = 0;
            if (valid_mem_addr(vm.pc) || valid_mem_addr(vm.pc + 3))
            {
                cur_inst = vm.M[vm.pc] | (vm.M[vm.pc + 1] << 8) |
                           (vm.M[vm.pc + 2] << 16) |
                           (vm.M[vm.pc + 3] << 24);
            }
            printf("Illegal Operation: 0x%08x\n", cur_inst);
            printf("PC = 0x%08x;\n", vm.pc);
            register_dump(&vm);
            free_all_mallocs(&vm);
            return RPR_SUCCESS;
        }
        break;
        }
    }
    free_all_mallocs(&vm);
    return RPR_SUCCESS;
}