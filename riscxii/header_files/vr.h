#ifndef VR_H
#define VR_H

#ifndef LOCAL_HEADERS
#define LOCAL_HEADERS
#include "./../header_files/loc_headers.h"
#endif

// VIRTUAL ROUTINE ADDRESSES

#define VR_CONSOLE_WRITE_CHAR 0x0800
#define VR_CONSOLE_WRITE_SIGNED_INT 0x0804
#define VR_CONSOLE_WRITE_UNSIGNED_INT 0x0808
#define VR_HALT 0x080C
#define VR_CONSOLE_READ_CHAR 0x0812
#define VR_READ_SIGNED_INT 0x0816
#define VR_CONSOLE_DUMP_PC 0x0820
#define VR_CONSOLE_DUMP_REGISTERS 0x0824
#define VR_CONSOLE_DUMP_MEMORY_WORD 0x0828
#define VR_MALLOC 0x0830
#define VR_FREE 0x0834

// This enum holds the return values for the virtual routine handler.
typedef enum
{
    VR_SUCCESS,
    // A store operation has accessed the halt
    // memory address
    VR_HALT_REQUESTED,
    // The memory address passed is not the memory address
    // of a virtual routine
    VR_INVALID_MEM_ADDR,
    VR_FAILURE,
    VR_FAILURE_MALLOC
} vr_handler_return;

// handles virtual routines
vr_handler_return vr_handler(int32_t mem_addr, int8_t rd, vm_state *vm, mem_unit size);

#endif