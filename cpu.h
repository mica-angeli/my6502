#ifndef MY6502_CPU_H
#define MY6502_CPU_H

#include <stdint.h>

#include "mem.h"

struct Cpu
{
  u_int16_t pc;
  u_int8_t sp;

  u_int8_t a, x, y;

  u_int8_t status;

  Mem* mem;

  u_int64_t cycles;
} typedef Cpu;

typedef enum {
  OP_LDA_IMMEDIATE = 0xa9,
  OP_LDA_ZERO_PAGE = 0xa5,
  OP_STA_ZERO_PAGE = 0x85,
  OP_STA_ABSOLUTE  = 0x8d,
} Opcodes;

void Cpu_ctor(Cpu* this, Mem* mem);

void Cpu_dtor(Cpu* this);

void Cpu_print(Cpu* this);

void Cpu_tick(Cpu* this);

void Cpu_run(Cpu* this);

#endif //MY6502_CPU_H
