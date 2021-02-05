#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "opcodes.h"

struct
{
  u_int8_t* data;
  size_t size;
} typedef Mem;

void Mem_ctor(Mem* this, size_t size)
{
  this->data = (uint8_t*) calloc(size, sizeof(uint8_t));
  this->size = size;
}

void Mem_dtor(Mem* this)
{
  free(this->data);
}

struct Cpu
{
  u_int16_t pc;
  u_int8_t sp;

  u_int8_t a, x, y;

  u_int8_t status;

  Mem* mem;

  u_int64_t cycles;
} typedef Cpu;

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
//  printf("pc = 0x%04x, sp = 0x%02x\n", this->pc, this->sp);
//  printf("a = 0x%02x, x = 0x%02x, y = 0x%02x\n", this->a, this->x, this->y);
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

int main() {
  Mem mem;
  Mem_ctor(&mem, 0x10000);
  Cpu c;
  Cpu_ctor(&c, &mem);

  Cpu_print(&c);

  // Load memory values
  mem.data[0x01] = 0x77;

  // Load program
  const uint8_t program[] = {
      OP_LDA_IMMEDIATE, 0x99,
      OP_LDA_ZERO_PAGE, 0x01,
      OP_STA_ZERO_PAGE, 0x02,
      OP_LDA_IMMEDIATE, 0xff,
      OP_STA_ABSOLUTE, 0x34, 0x12
  };
  memcpy(mem.data + 0x600, program, sizeof(program));

  // Run cpu
  Cpu_run(&c);

  printf("\n%02x %02x", mem.data[0x02], mem.data[0x1234]);

  Cpu_dtor(&c);
  Mem_dtor(&mem);
  return 0;
}
