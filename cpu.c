#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"

void Cpu_ctor(Cpu* this, Mem* mem)
{
  this->pc = 0x600;
  this->mem = mem;
  this->cycles = 0;
}

void Cpu_dtor(Cpu* this)
{
  // nothing
}

void Cpu_print(Cpu* this)
{
  printf("\n#%llu PC:%04X SP:%02X A:%02X X:%02X Y:%02X", this->cycles, this->pc, this->sp, this->a, this->x, this->y);
}

void Cpu_tick(Cpu* this)
{
  char op_str[128];
  const uint8_t* pc_ptr = this->mem->data + this->pc;
  const uint8_t op = pc_ptr[0];
//const uint8_t op = this->mem->data[this->pc];
  switch(op)
  {
    case OP_LDA_IMMEDIATE:
    {
      this->a = pc_ptr[1];
      this->pc += 2;
      this->cycles += 2;

      snprintf(op_str, 128, "LDA #%02X", pc_ptr[1]);
      break;
    }
    case OP_LDA_ZERO_PAGE:
    {
      this->a = this->mem->data[pc_ptr[1]];
      this->pc += 2;
      this->cycles += 3;

      snprintf(op_str, 128, "LDA $%02X", pc_ptr[1]);
      break;
    }
    case OP_STA_ZERO_PAGE:
    {
      this->mem->data[pc_ptr[1]] = this->a;
      this->pc += 2;
      this->cycles += 3;

      snprintf(op_str, 128, "STA $%02X", pc_ptr[1]);
      break;
    }
    case OP_STA_ABSOLUTE:
    {
      const uint16_t addr = pc_ptr[1] | (pc_ptr[2] << 8);
      this->mem->data[addr] = this->a;
      this->pc += 3;
      this->cycles += 4;

      snprintf(op_str, 128, "STA $%04X", addr);
      break;
    }
    case OP_JMP_ABSOLUTE:
    {
      const uint16_t addr = pc_ptr[1] | (pc_ptr[2] << 8);
      this->pc = addr;
      this->cycles += 3;

      snprintf(op_str, 128, "JMP $%04X", addr);
      break;
    }
    case OP_JMP_INDIRECT:
    {
      const uint16_t indirect_addr = pc_ptr[1] | (pc_ptr[2] << 8);
      const uint16_t addr = this->mem->data[indirect_addr] | (this->mem->data[indirect_addr + 1] << 8);
      this->pc = addr;
      this->cycles += 5;

      snprintf(op_str, 128, "JMP $(%04X)", indirect_addr);
      break;
    }
    default:
      break;
  }

  Cpu_print(this);
  printf("  \e[1;34m%s\e[0m", op_str);
}

void Cpu_run(Cpu* this)
{
  while(this->mem->data[this->pc] != 0)
  {
    Cpu_tick(this);
  }
}
