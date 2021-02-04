#ifndef MY6502_OPCODES_H
#define MY6502_OPCODES_H

typedef enum {
  OP_LDA_IMMEDIATE = 0xa9,
  OP_LDA_ZERO_PAGE = 0xa5
} Opcodes;

#endif //MY6502_OPCODES_H
