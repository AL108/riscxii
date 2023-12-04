#ifndef LOCAL_HEADERS
#define LOCAL_HEADERS
#include "./../header_files/loc_headers.h"
#endif

#include <stdlib.h>
#include <stdbool.h>

bool valid_mem_addr(int32_t mem_addr)
{
    return (IN_RANGE(mem_addr, INST_MEM_START_ADDR, HEAP_BANKS_MEM_END_ADDR));
}

void register_dump(const vm_state *vm)
{
    for (int i = 0; i < REGISTER_COUNT; i++)
    {
        printf("R[%d] = 0x%08x;\n", i, vm->R[i]);
    }
}

bool init_vm(vm_state *vm, const char *mi_filepath)
{
    // SET ALL MEMORY ENTRIES TO 0

    int32_t i = MEM_SIZE_IN_BYTES;
    i--;
    while (i >= 0)
    {
        vm->M[i--] = 0;
    }

    // LOAD MEMORY IMAGE

    if (!load_image(vm, mi_filepath))
    {
        return false;
    }

    // SET ALL REGISTERS TO 0

    i = 0;
    while (i < REGISTER_COUNT)
    {
        vm->R[i++] = 0;
    }

    // SET PTR TO MALLOC TRACKING LIST TO NULL
    // AND SET PC TO THE FIRST INSTRUCTION

    vm->cur_mallocs = NULL;
    vm->pc = INST_MEM_START_ADDR;

    return true;
}

bool load_image(vm_state *vm, const char *filepath)
{
    FILE *image_ptr = fopen(filepath, "rb");
    if (image_ptr == NULL)
    {
        return false;
    }
    // LOAD INSTRUCTION MEMORY AND DATA MEMORY
    fread(vm->M, sizeof(uint8_t),
          INST_MEM_SIZE_IN_WORDS * WORD_SIZE_IN_BYTES +
              DATA_MEM_SIZE_IN_WORDS * WORD_SIZE_IN_BYTES,
          image_ptr);
    fclose(image_ptr);
    return true;
}

// HEAP BANK FUNCTIONS

#define ROUND_UP_TO_NEAREST_64_MULTIPLE(x) (((x) % 64 == 0) ? x : (((x) / 64) + 1) * 64)

bool addr_malloced(vm_state *vm, int32_t addr)
{
    int32_t cur_mal_start;
    int32_t cur_mal_end;
    malloc_record *mallocs_ptr = vm->cur_mallocs;
    while (mallocs_ptr)
    {
        cur_mal_start = mallocs_ptr->addr;
        cur_mal_end = cur_mal_start + mallocs_ptr->size;
        if (IN_RANGE(addr, cur_mal_start, cur_mal_end))
        {
            return true;
        }
        mallocs_ptr = mallocs_ptr->next;
    }
    return false;
}

bool block_is_free(vm_state *vm, int32_t addr)
{
    if (!IN_RANGE(addr, HEAP_BANKS_MEM_START_ADDR,
                  HEAP_BANKS_MEM_END_ADDR - HEAP_BANK_SIZE_IN_WORDS *
                                                WORD_SIZE_IN_BYTES))
    {
        return false;
    }
    if ((addr - HEAP_BANKS_MEM_START_ADDR) % 64 != 0)
    {
        return false;
    }
    // This works because all mallocs are blocks,
    // i.e. 1) multiple of 64 offset from the beginning of the
    // heap region
    //      2) multiple of 64 size
    return !addr_malloced(vm, addr);
}

bool region_is_free(vm_state *vm, int32_t addr, int32_t size)
{
    // returns false if the region is not free or if the addr
    // is not of the start of a heap block
    if ((addr - HEAP_BANKS_MEM_START_ADDR) % 64 != 0)
    {
        return false;
    }
    int32_t actual_region_size = ROUND_UP_TO_NEAREST_64_MULTIPLE(size);
    for (int32_t x = addr; x < addr + actual_region_size;
         x += 64)
    {
        if (!block_is_free(vm, x))
        {
            return false;
        }
    }
    return true;
}

// 'malloc_' does 1. if there is a sufficiently large contiguous
// region in the heap available, otherwise it does 2.
// 1. set R[28] to a memory address to a heap bank region,
// while updating the cur_mallocs datastructure accordingly.
// 2. set R[28] to 0.

bool malloc_(vm_state *vm, int32_t size)
{
    if (size <= 0)
    {
        vm->R[28] = 0;
        return false;
    }
    // look for the first unallocated contiguous heap region that is sufficiently large
    int32_t region_addr = -1;
    int32_t rounded_up_sz;
    for (int32_t addr = HEAP_BANKS_MEM_START_ADDR; addr < HEAP_BANKS_MEM_END_ADDR;
         addr += 64)
    {
        if (region_is_free(vm, addr, size))
        {
            region_addr = addr;
            rounded_up_sz = ROUND_UP_TO_NEAREST_64_MULTIPLE(size);
            break;
        }
    }
    if (region_addr == -1) // region not found
    {
        vm->R[28] = 0;
        return false;
    }
    else // region found
    {
        // update data structure
        vm->R[28] = region_addr;
        // update the malloc tracking datastructure 'cur_mallocs'
        malloc_record *new_malloc_record = malloc(sizeof(malloc_record));
        new_malloc_record->addr = region_addr;
        new_malloc_record->size = rounded_up_sz / 2; // TODO: FIX
        new_malloc_record->next = vm->cur_mallocs;
        vm->cur_mallocs = new_malloc_record;
    }
    return true;
}

bool free_(vm_state *vm, int32_t addr)
{
    // search the cur_mallocs linked list for the node representing
    // the allocation (if exists) starting at 'addr'
    malloc_record *mallocs_ptr = vm->cur_mallocs;
    malloc_record *mallocs_ptr_prev = NULL;
    bool addr_found = false;
    while (mallocs_ptr)
    {
        if (mallocs_ptr->addr == addr)
        {
            addr_found = true;
            if (mallocs_ptr_prev == NULL)
            {
                if (mallocs_ptr->next == NULL)
                {
                    // there is only one cur_mallocs entry
                    vm->cur_mallocs = NULL;
                }
                else
                {
                    // there are multiple cur_mallocs entries
                    vm->cur_mallocs = mallocs_ptr->next;
                }
            }
            else
            {
                mallocs_ptr_prev->next = mallocs_ptr->next;
            }
            free(mallocs_ptr);
            break;
        }
        mallocs_ptr_prev = mallocs_ptr;
        mallocs_ptr = mallocs_ptr->next;
    }
    if (!addr_found)
    {
        return false;
    }
    return true;
}

void free_all_mallocs(vm_state *vm)
{
    malloc_record *mallocs_ptr = vm->cur_mallocs;
    malloc_record *mallocs_ptr_prev = NULL;
    while (mallocs_ptr != NULL)
    {
        if (mallocs_ptr_prev != NULL)
        {
            free(mallocs_ptr_prev);
        }
        mallocs_ptr_prev = mallocs_ptr;
        mallocs_ptr = mallocs_ptr->next;
    }
    if (mallocs_ptr_prev != NULL)
    {
        free(mallocs_ptr_prev);
    }
}