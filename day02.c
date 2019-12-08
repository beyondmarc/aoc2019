#if 0
#!/ usr / bin / env bash

set -e

if [ ! -d "build" ]; then
  mkdir build
fi

#args = "1,1,1,4,99,5,6,0,99"
args="1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,1,10,19,1,6,19,23,2,23,6,27,2,6,27,31,2,13,31,35,1,10,35,39,2,39,13,43,1,43,13,47,1,6,47,51,1,10,51,55,2,55,6,59,1,5,59,63,2,9,63,67,1,6,67,71,2,9,71,75,1,6,75,79,2,79,13,83,1,83,10,87,1,13,87,91,1,91,10,95,2,9,95,99,1,5,99,103,2,10,103,107,1,107,2,111,1,111,5,0,99,2,14,0,0"

name=`basename "$0" .c`

clang -O2 -std=gnu11 -g $name.c -o build/$name

build/$name $args

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

#define MEM_SIZE 1024

char* str_find_comma(char* str) {
  char* r = str;
  while (*r && *r != ',') {
    r++;
  }
  return r;
}

void run(S32* memory, S32 count) {
  S32 ip = 0;
  for (;;) {
    B32 halt = 0;

    switch (memory[ip]) {
      case 1: {
        // add
        S32 op0 = memory[ip + 1];
        S32 op1 = memory[ip + 2];
        S32 res = memory[ip + 3];

        memory[res] = memory[op0] + memory[op1];

        ip += 4;
      } break;
      case 2: {
        // mul
        S32 op0 = memory[ip + 1];
        S32 op1 = memory[ip + 2];
        S32 res = memory[ip + 3];

        memory[res] = memory[op0] * memory[op1];

        ip += 4;
      } break;
      case 99: {
        // halt execution
        halt = 1;
      } break;
    }

    if (halt || ip > count) {
      break;
    }
  }
}

S32 main(S32 argc, char** argv) {
  // PART I: make "computer" and run the incodes
  // PART II: find the inputs that produce a given result
  S32 exec = 2;

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

    if (exec == 1) {
      // "fix" memory
      memory[1] = 12;
      memory[2] = 2;

      // run program in memory
      run(memory, count);
    } else {
      S32 mem_cpy[MEM_SIZE];

      S32 desired_output = 19690720;

      // find inputs that give desired output
      S32 noun = -1;
      S32 verb = -1;
      do {
        for (S32 ni = 0; ni <= 99; ++ni) {
          for (S32 vi = 0; vi <= 99; ++vi) {
            memcpy(mem_cpy, memory, count * sizeof(S32));

            mem_cpy[1] = noun = ni;
            mem_cpy[2] = verb = vi;

            run(mem_cpy, count);

            if (mem_cpy[0] == desired_output) {
              memcpy(memory, mem_cpy, count * sizeof(S32));
              break;
            }
          }
          if (mem_cpy[0] == desired_output) break;
        }
      } while (mem_cpy[0] != desired_output);

      printf("noun = %d, verb = %d (answer = %d)\n", noun, verb,
             100 * noun + verb);
    }

    // print memory
    for (S32 i = 0; i < count; ++i) {
      if (i < count - 1)
        printf("%d,", memory[i]);
      else
        printf("%d", memory[i]);
    }
    printf("\n");
  }

  return 0;
}
