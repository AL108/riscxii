// THIS HEADER FILE IS USED TO INCLUDE ALL HEADER FILES AT ONCE.

#ifndef LOC_HEADERS_H
#define LOC_HEADERS_H

// memory.h and memory.c relate to managing the storage of
// a vm state. That is, the registers, pc, memory areas,
// malloc-tracking, etc.
#include "mem.h"

// instruction_format.h includes macros relating to how instructions are
// formatted.
#include "inst_format.h"

// the vr source and headers contain functions for carrying out virtual
// routines.
#include "vr.h"

// The al_inst, mem_inst and prog_inst header and source files contain
// functions for handling instructions that have been parsed by
// functions from inst_processing.
#include "al_inst.h"
#include "mem_inst.h"
#include "prog_inst.h"

// The inst_processing source and header files contain functions and macros
// for reading raw instructions, parsing them and calling the correct
// instruction handler function in 'al_inst', 'mem_inst' or 'prog_inst'.
#include "inst_processing.h"

#endif