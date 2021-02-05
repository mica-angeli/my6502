#include "mem.h"

void Mem_ctor(Mem* this, size_t size)
{
  this->data = (uint8_t*) calloc(size, sizeof(uint8_t));
  this->size = size;
}

void Mem_dtor(Mem* this)
{
  free(this->data);
}
