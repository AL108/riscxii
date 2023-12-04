#ifndef MEM_INST_H
#define MEM_INST_H

#ifndef LOCAL_HEADERS
#define LOCAL_HEADERS
#include "./../header_files/loc_headers.h"
#endif

// This is the return typedef for the load and store functions
typedef enum
{
    // The load was successful
    LR_LOAD_SUCCESS,
    // The load operation encountered an unknown error
    LR_LOAD_UNKNOWN_ERR,
    // The load operation tried to do something illegal
    LR_ILLEGAL
} load_ret;

typedef enum
{
    // The store operation triggered a halt virtual routine
    SR_HALT_REQUESTED,
    // The store was successful
    SR_STORE_SUCCESS,
    // The store or load operation tried to do something illegal
    SR_ILLEGAL
} store_ret;

// the 'load' function is used to handle all load instructions.
// For example, lb would be handled by load through passing
// true into the signed parametera and BYTE into the size parameter.
load_ret load(vm_state *vm, int8_t rd, int8_t rs1, int16_t imm,
              mem_unit size, bool signed_);

// Similar ot the 'load' function, the store function is used to handle
// all load instructions.
store_ret store(vm_state *vm, int8_t rs1, int8_t rs2, int16_t imm,
                mem_unit size);

#endif