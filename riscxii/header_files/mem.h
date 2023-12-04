
#ifndef MEM_H
#define MEM_H

#ifndef LOCAL_HEADERS
#define LOCAL_HEADERS
#include "./../header_files/loc_headers.h"
#endif

#include <stdint.h>
#include <stdbool.h>

// instruction size in bytes
#define INST_SZ 4

// SIZES OF MEMORY AREAS AND RELATED

#define INST_MEM_SIZE_IN_WORDS (256)
#define DATA_MEM_SIZE_IN_WORDS (256)
#define VIRT_ROUT_MEM_SIZE_IN_WORDS (64)
#define HEAP_BANKS_MEM_SIZE_IN_WORDS (2048)
#define HEAP_BANK_COUNT (128)
#define HEAP_BANK_SIZE_IN_WORDS (16)
#define MEM_BUF_SIZE_IN_WORDS (0)
#define REGISTER_SIZE_IN_WORDS (1)
#define REGISTER_COUNT (32)
#define WORD_SIZE_IN_BYTES (4)
#define WORD_SIZE_IN_BITS (32)
#define MEM_SIZE_IN_BYTES (0xd800)

// STARTING AND ENDING ADDRESSESS OF MEMORY AREAS

#define INST_MEM_START_ADDR (0x0000)
#define INST_MEM_END_ADDR (0x03FF)
#define DATA_MEM_START_ADDR (0x0400)
#define DATA_MEM_END_ADDR (0x07FF)
#define VIRT_ROUT_MEM_START_ADDR (0x0800)
#define VIRT_ROUT_MEM_END_ADDR (0x08FF)
#define HEAP_BANKS_MEM_START_ADDR (0xb700)
#define HEAP_BANKS_MEM_END_ADDR (0xd700)

// 'malloc_record' is a linked-list node. The linked
// list keeps track of heap allocations.
typedef struct malloc_record
{
    int32_t addr;
    int32_t size;
    struct malloc_record *next;
} malloc_record;

typedef enum
{
    BYTE,
    HALFWORD,
    WORD
} mem_unit;

// 'vm_state' holds all the state information about a vm.
typedef struct
{
    // M is all of a vm state's memory, apart from the
    // registers, malloc tracking list and pc.
    // unsigned so that we don't need as many casts when bitshifting
    uint8_t M[MEM_SIZE_IN_BYTES];
    int32_t R[REGISTER_COUNT]; // registers
    // malloc tracking linked list (ptr to head)
    malloc_record *cur_mallocs;
    // program counter: holds the index of the current instruction in 'M'.
    int32_t pc;
} vm_state;

// sets the start state of a vm and loads a memory image
bool init_vm(vm_state *vm, const char *mi_filepath);

// prints registers values to stdout
void register_dump(const vm_state *vm);

// loads a memory image into the instructions area of a
// vm state
bool load_image(vm_state *vm, const char *mi_filepath);

// HEAP BANK FUNCTIONS

// returns whether the memory entry addressed by
// 'addr' is in a currently allocated heap region.
bool addr_malloced(vm_state *vm, int32_t addr);

// Attempts to allocate a heap region with size >= size and
// size % 64 = 0. Upon success, the region address is stored
// in R[28]. Upon failure, R[28] is set to 0.
bool malloc_(vm_state *vm, int32_t size);

// Attempts to free an allocated region of memory starting at 'addr'.
// Upon success, true is returned. Upon failure, false is returned.
bool free_(vm_state *vm, int32_t addr);

// Frees all allocated heap memory
void free_all_mallocs(vm_state *vm);

// Checks if the region beginning at addr and ending at addr + size
// is a free region of memory in the heap.
bool region_is_free(vm_state *vm, int32_t addr, int32_t size);

// Checks if the 64B heap block beginning at 'addr' is free.
// False is returned if 'addr' is not the start of a 64B unallocatd
// heap block. Also, false is returned if 'addr' is not
// a multiple of 64B from the start of the heap memory area.
bool block_is_free(vm_state *vm, int32_t addr);

bool in_vr_region(int32_t addr);
bool in_hb_region(int32_t addr);
bool in_data_region(int32_t addr);

bool valid_mem_addr(int32_t mem_addr);

#define IS_REGISTER(val) ((val) >= 0 && (val) <= 31)
#define IN_RANGE(val, l, r) ((val) >= (l) && (val) <= (r))

#endif