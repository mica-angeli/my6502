#include <memory.h>
#include <stdio.h>
#include <stdint.h>

#include "mem.h"
#include "cpu.h"

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
      OP_STA_ABSOLUTE, 0x34, 0x12,
      OP_JMP_INDIRECT, 0x77, 0x77,
//      OP_JMP_ABSOLUTE, 0x00, 0x06,
  };
  memcpy(mem.data + 0x600, program, sizeof(program));

  // Run cpu
  Cpu_run(&c);

  printf("\n%02x %02x", mem.data[0x02], mem.data[0x1234]);

  Cpu_dtor(&c);
  Mem_dtor(&mem);
  return 0;
}
