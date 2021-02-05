#ifndef MY6502_MEM_H
#define MY6502_MEM_H

#include <stdlib.h>

struct
{
  u_int8_t* data;
  size_t size;
} typedef Mem;

void Mem_ctor(Mem* this, size_t size);

void Mem_dtor(Mem* this);

#endif //MY6502_MEM_H
