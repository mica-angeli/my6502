#ifndef MY6502_OPCODES_H
#define MY6502_OPCODES_H

typedef enum {
  OP_LDA_IMMEDIATE = 0xa9,
  OP_LDA_ZERO_PAGE = 0xa5,
  OP_STA_ZERO_PAGE = 0x85,
  OP_STA_ABSOLUTE  = 0x8d,
} Opcodes;

#endif //MY6502_OPCODES_H
