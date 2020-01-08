#if 0
#! /usr/bin/env bash

set -e

if [ ! -d "build" ]; then
  mkdir build
fi

args="3,9,8,9,10,9,4,9,99,-1,8"
#args="3,225,1,225,6,6,1100,1,238,225,104,0,1102,35,92,225,1101,25,55,225,1102,47,36,225,1102,17,35,225,1,165,18,224,1001,224,-106,224,4,224,102,8,223,223,1001,224,3,224,1,223,224,223,1101,68,23,224,101,-91,224,224,4,224,102,8,223,223,101,1,224,224,1,223,224,223,2,217,13,224,1001,224,-1890,224,4,224,102,8,223,223,1001,224,6,224,1,224,223,223,1102,69,77,224,1001,224,-5313,224,4,224,1002,223,8,223,101,2,224,224,1,224,223,223,102,50,22,224,101,-1800,224,224,4,224,1002,223,8,223,1001,224,5,224,1,224,223,223,1102,89,32,225,1001,26,60,224,1001,224,-95,224,4,224,102,8,223,223,101,2,224,224,1,223,224,223,1102,51,79,225,1102,65,30,225,1002,170,86,224,101,-2580,224,224,4,224,102,8,223,223,1001,224,6,224,1,223,224,223,101,39,139,224,1001,224,-128,224,4,224,102,8,223,223,101,3,224,224,1,223,224,223,1102,54,93,225,4,223,99,0,0,0,677,0,0,0,0,0,0,0,0,0,0,0,1105,0,99999,1105,227,247,1105,1,99999,1005,227,99999,1005,0,256,1105,1,99999,1106,227,99999,1106,0,265,1105,1,99999,1006,0,99999,1006,227,274,1105,1,99999,1105,1,280,1105,1,99999,1,225,225,225,1101,294,0,0,105,1,0,1105,1,99999,1106,0,300,1105,1,99999,1,225,225,225,1101,314,0,0,106,0,0,1105,1,99999,1008,677,677,224,1002,223,2,223,1005,224,329,101,1,223,223,7,677,677,224,102,2,223,223,1006,224,344,101,1,223,223,108,677,677,224,1002,223,2,223,1006,224,359,1001,223,1,223,7,677,226,224,1002,223,2,223,1005,224,374,1001,223,1,223,1107,677,226,224,1002,223,2,223,1005,224,389,1001,223,1,223,107,226,677,224,102,2,223,223,1005,224,404,1001,223,1,223,1108,226,677,224,1002,223,2,223,1006,224,419,101,1,223,223,107,226,226,224,102,2,223,223,1005,224,434,1001,223,1,223,108,677,226,224,1002,223,2,223,1006,224,449,101,1,223,223,108,226,226,224,102,2,223,223,1006,224,464,1001,223,1,223,1007,226,226,224,1002,223,2,223,1005,224,479,101,1,223,223,8,677,226,224,1002,223,2,223,1006,224,494,101,1,223,223,1007,226,677,224,102,2,223,223,1006,224,509,101,1,223,223,7,226,677,224,1002,223,2,223,1005,224,524,101,1,223,223,107,677,677,224,102,2,223,223,1005,224,539,101,1,223,223,1008,677,226,224,1002,223,2,223,1005,224,554,1001,223,1,223,1008,226,226,224,1002,223,2,223,1006,224,569,1001,223,1,223,1108,226,226,224,102,2,223,223,1005,224,584,101,1,223,223,1107,226,677,224,1002,223,2,223,1005,224,599,1001,223,1,223,8,226,677,224,1002,223,2,223,1006,224,614,1001,223,1,223,1108,677,226,224,102,2,223,223,1005,224,629,1001,223,1,223,8,226,226,224,1002,223,2,223,1005,224,644,1001,223,1,223,1107,677,677,224,1002,223,2,223,1005,224,659,1001,223,1,223,1007,677,677,224,1002,223,2,223,1005,224,674,101,1,223,223,4,223,99,226"

name=`basename "$0" .c`

clang -O2 -std=gnu11 -g $name.c -o build/$name

#build/$name $args

exit 0
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef signed char S8;
typedef signed short S16;
typedef signed int S32;
typedef signed long long S64;
typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
typedef unsigned long long U64;

typedef S8 B8;
typedef S16 B16;
typedef S32 B32;
typedef S64 B64;

typedef float F32;
typedef float F64;

typedef S32 S32x;
typedef U32 U32x;
typedef S64 S64x;
typedef U64 U64x;

void print_msg(char *msg, ...) {
  va_list args;
  va_start(args, msg);
  vprintf(msg, args);
  va_end(args);
}

#define ASSERT(cond, msg, ...)   \
  if (!(cond)) {                 \
    print_msg(msg, __VA_ARGS__); \
    *(volatile S32 *)0;          \
  }

#define TRACE(msg, ...)        \
  print_msg(msg, __VA_ARGS__);

#define MEM_SIZE 4096
#define PARAM_MAX_COUNT 3

typedef enum {
  OPCODE_ADD = 1,
  OPCODE_MUL = 2,
  OPCODE_INPUT = 3,
  OPCODE_OUTPUT = 4,
  OPCODE_JUMP_IF_TRUE = 5,
  OPCODE_JUMP_IF_FALSE = 6,
  OPCODE_LESS_THAN = 7,
  OPCODE_EQUALS = 8,
  OPCODE_HALT = 99,
} Opcode;

typedef enum {
  PARAM_MODE_POS = 0,  // position mode
  PARAM_MODE_IMM = 1,  // immediate mode
} Param_Mode;

char* str_find_comma(char* str) {
  char* r = str;
  while (*r && *r != ',') {
    r++;
  }
  return r;
}

void print_memory(S32* memory, S32 count) {
  for (S32 i = 0; i < count; ++i) {
    if (i < count - 1)
      printf("%d,", memory[i]);
    else
      printf("%d", memory[i]);
  }
  printf("\n");
}

void run(S32* memory, S32 count) {
  S32 ip = 0;
  for (;;) {
    B32 halt = 0;

    // decode instruction
    Opcode opcode;
    Param_Mode param_modes[PARAM_MAX_COUNT];

    S32 instruction = memory[ip];
    opcode = instruction % 100;
    instruction /= 100;

    for (S32 pm_idx = 0; pm_idx < PARAM_MAX_COUNT; ++pm_idx) {
      param_modes[pm_idx] = instruction % 10;
      instruction /= 10;
    }

    switch (opcode) {
      case OPCODE_ADD: {
        S32 op0 = memory[ip + 1];
        S32 op1 = memory[ip + 2];
        S32 res = memory[ip + 3];

        S32 p0_val = param_modes[0] == PARAM_MODE_POS ? memory[op0] : op0;
        S32 p1_val = param_modes[1] == PARAM_MODE_POS ? memory[op1] : op1;

        memory[res] = p0_val + p1_val;

        ip += 4;
      } break;
      case OPCODE_MUL: {
        S32 op0 = memory[ip + 1];
        S32 op1 = memory[ip + 2];
        S32 res = memory[ip + 3];

        S32 p0_val = param_modes[0] == PARAM_MODE_POS ? memory[op0] : op0;
        S32 p1_val = param_modes[1] == PARAM_MODE_POS ? memory[op1] : op1;

        memory[res] = p0_val * p1_val;

        ip += 4;
      } break;
      case OPCODE_INPUT: {
        S32 op0 = memory[ip + 1];

        printf("Input: \n");
        S32 input;
        scanf("%d", &input);

        memory[op0] = input;

        ip += 2;
      } break;
      case OPCODE_OUTPUT: {
        S32 op0 = memory[ip + 1];
        printf("Output: %d\n", memory[op0]);

        ip += 2;
      } break;
      case OPCODE_JUMP_IF_TRUE: {
        S32 op0 = memory[ip + 1];
        S32 op1 = memory[ip + 2];

        S32 p0_val = param_modes[0] == PARAM_MODE_POS ? memory[op0] : op0;
        S32 p1_val = param_modes[1] == PARAM_MODE_POS ? memory[op1] : op1;

        if (p0_val) {
          ip = p1_val;
        } else {
          ip += 3;
        }
      } break;
      case OPCODE_JUMP_IF_FALSE: {
        S32 op0 = memory[ip + 1];
        S32 op1 = memory[ip + 2];

        S32 p0_val = param_modes[0] == PARAM_MODE_POS ? memory[op0] : op0;
        S32 p1_val = param_modes[1] == PARAM_MODE_POS ? memory[op1] : op1;

        if (!p0_val) {
          ip = p1_val;
        } else {
          ip += 3;
        }
      } break;
      case OPCODE_LESS_THAN: {
        S32 op0 = memory[ip + 1];
        S32 op1 = memory[ip + 2];
        S32 res = memory[ip + 3];

        S32 p0_val = param_modes[0] == PARAM_MODE_POS ? memory[op0] : op0;
        S32 p1_val = param_modes[1] == PARAM_MODE_POS ? memory[op1] : op1;

        memory[res] = p0_val < p1_val;

        ip += 4;
      } break;
      case OPCODE_EQUALS: {
        S32 op0 = memory[ip + 1];
        S32 op1 = memory[ip + 2];
        S32 res = memory[ip + 3];

        S32 p0_val = param_modes[0] == PARAM_MODE_POS ? memory[op0] : op0;
        S32 p1_val = param_modes[1] == PARAM_MODE_POS ? memory[op1] : op1;

        memory[res] = p0_val == p1_val;

        ip += 4;
      } break;
      case OPCODE_HALT: {
        halt = 1;
      } break;
      default: {
        ASSERT(0, "Opcode not found!\n", 0);
      } break;
    }

    if (halt || ip > count) {
      break;
    }
  }
}

S32 main(S32 argc, char** argv) {
  // PART I: update "computer" from day02 with input/output opcodes and
  // parameter modes (input = 1)
  // PART II: add jump if true/false and less than / equal opcodes (input = 5)

  if (argc > 1) {
    char* program_str = argv[1];
    S32 memory[MEM_SIZE];

    // read memory
    S32 count = 0;
    S32 len = strlen(program_str);
    char* program_str_end = program_str + len;

    while (program_str < program_str_end) {
      char* comma = str_find_comma(program_str);

      S32 code = strtol(program_str, &comma, 10);
      memory[count++] = code;

      program_str = comma + 1;
    }

    // run program in memory
    run(memory, count);
  }

  return 0;
}

