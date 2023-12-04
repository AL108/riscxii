#ifndef INST_PROCESSING_H
#define INST_PROCESSING_H
#ifndef LOCAL_HEADERS
#define LOCAL_HEADERS
#include "./../header_files/loc_headers.h"
#endif
#include <stdio.h>

// BITMASKS FOR EXTRACTING INSTRUCTION FIELDS

#define EXTRACT_OPCODE(x) ((x)&0x7f)
#define EXTRACT_RD(x) (((x)&0xf80) >> RD_START)
#define EXTRACT_FUNC3(x) (((x)&0x7000) >> FUNC3_START)
#define EXTRACT_FUNC7(x) (((x)&0xfe000000) >> FUNC7_START)
#define EXTRACT_RS1(x) (((x)&0xf8000) >> RS1_START)
#define EXTRACT_RS2(x) (((x)&0x1f00000) >> RS2_START)

// imm of type I instructions
#define EXTRACT_IMM_I(x) (((x)&0xfff00000) >> I_IMM_0_TO_11_START)

// imm of type S instructions
#define EXTRACT_IMM_S_0_TO_4(x) (((x)&0xf80) >> S_IMM_0_TO_4_START)
#define EXTRACT_IMM_S_5_TO_11(x) (((x)&0xfe000000) >> S_IMM_5_TO_11_START)
#define EXTRACT_IMM_S(x)      \
    EXTRACT_IMM_S_0_TO_4(x) | \
        (EXTRACT_IMM_S_5_TO_11(x) << 5)

// imm of type SB instructions
#define EXTRACT_IMM_SB_11(x) (((x)&0x80) >> SB_IMM_11)
#define EXTRACT_IMM_SB_1_TO_4(x) (((x)&0x1E00) >> SB_IMM_1_TO_4_START)
#define EXTRACT_IMM_SB_5_TO_10(x) (((x)&0x7E000000) >> SB_IMM_5_TO_10_START)
#define EXTRACT_IMM_SB_12(x) (((x)&0x80000000) >> SB_IMM_12)
#define EXTRACT_IMM_SB(x)                  \
    EXTRACT_IMM_SB_1_TO_4(x) |             \
        (EXTRACT_IMM_SB_5_TO_10(x) << 5) | \
        (EXTRACT_IMM_SB_11(x) << 11) |     \
        (EXTRACT_IMM_SB_12(x) << 12)

// imm of type U instructions
#define EXTRACT_IMM_U(x) (((x)&0xFFFFF000) >> U_IMM_12_TO_31_START)

// imm of type UJ instructions
#define EXTRACT_IMM_UJ_12_TO_19(x) (((x)&0xff000) >> UJ_IMM_12_TO_19_START)
#define EXTRACT_IMM_UJ_11(x) (((x)&0x100000) >> UJ_IMM_11)
#define EXTRACT_IMM_UJ_1_TO_10(x) (((x)&0x7FE00000) >> (UJ_IMM_1_TO_10_START))
#define EXTRACT_IMM_UJ_20(x) (((x)&0x80000000) >> UJ_IMM_20)
#define EXTRACT_IMM_UJ(x)                    \
    EXTRACT_IMM_UJ_1_TO_10(x) |              \
        (EXTRACT_IMM_UJ_11(x) << 10) |       \
        (EXTRACT_IMM_UJ_12_TO_19(x) << 11) | \
        (EXTRACT_IMM_UJ_20(x) << 19)

// resolves to whether a 'sz' bit integer 'x' is negative
#define IS_NEG(x, sz) ((((x) >> ((sz)-1)) & 1) == 1)

// sign extend a number 'x' with 'sz' bits to 32 bits.
#define SEXT(x, sz) \
    IS_NEG(x, sz) ? ((x) | (0xffffffff << sz)) : (x)

// MACROS FOR EXTRACTING BYTES OUT OF A WORD, I.E.
// A FOUR BYTE TYPE E.G. 'int32_t'

#define EXTRACT_WBYTE1(x) ((x)&0xFF)
#define EXTRACT_WBYTE2(x) (((x) >> 8) & 0xFF)
#define EXTRACT_WBYTE3(x) (((x) >> 16) & 0xFF)
#define EXTRACT_WBYTE4(x) (((x) >> 24) & 0xFF)

// MACROS FOR COMBINING BYTES

// combines four bytes into a word
// Note: the &s ensure that the
// shift is logical and not arithmetic.
#define COMBINE_BYTES(b1, b2, b3, b4) \
    (b1) |                            \
        (((b2) << 8) & 0xff00) |      \
        (((b3) << 16) & 0xff0000) |   \
        (((b4) << 24) & 0xff000000)

// This typedef'd enum stores return values for 'run_inst_ret'
typedef enum
{
    // The instruction ran successfully has not set the pc.
    RIR_PC_UNSET,
    // The instruction ran successfully and has set the pc.
    RIR_PC_SET,
    // The bits encountered do not represent a recognised
    // instruction.
    RIR_INST_UNIMPLEMENTED,
    // The instruction ran successfully and requests that
    // vm halts.
    RIR_HALT_REQUESTED,
    // There are no remaining instructions
    RIR_PROGRAM_COMPLETE,
    // The instruction most recently run attempted to
    // do something illegal.
    RIR_ILLEGAL_OP
} run_inst_ret;

// This typedef'd enum stores the return values for the 'run_prog' function
typedef enum
{
    // The program ran successfully
    RPR_SUCCESS,
    // The memory image load failed
    RPR_FAILED_MI_LOAD
} run_prog_ret;

// run the program of the loaded memory image. That is,
// execute the instructions
run_prog_ret run_prog(const char *filepath);

// run the instruction at the address currently helf by the pc
run_inst_ret run_inst(vm_state *vm);

#endif