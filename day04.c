#if 0
#!/ usr / bin / env bash

set -e

if [ ! -d "build" ]; then
  mkdir build
fi

args="183564 657474"

name=`basename "$0" .c`

clang -O0 -std=gnu11 -g $name.c -o build/$name

build/$name $args

exit 0
#endif

#include <stdint.h>
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

void print_digits(U32 value, U32 digits[6]) {
  printf("Value: %u - Digits: [%u][%u][%u][%u][%u][%u]\n", value, digits[0],
         digits[1], digits[2], digits[3], digits[4], digits[5]);
}

typedef struct {
  U32 digit;
  U32 run_length;
} Repeat_Record;

S32 main(S32 argc, char **argv) {
  if (argc == 3) {
    U32 first = strtoul(argv[1], NULL, 10);
    U32 last = strtoul(argv[2], NULL, 10);
    printf("Range: %u-%u\n", first, last);

    U32 matches = 0;

    U32 count = last - first + 1;
    for (U32 i = 0; i < count; ++i) {
      U32 candidate = first + i;

      U32 digits[6];
      for (U32 d = 0; d < 6; ++d) {
        digits[5 - d] = candidate % 10;
        candidate /= 10;
      }

      if (i == 0) {
        print_digits(candidate, digits);
      }

      // PART I: candidates have increasing digits and consecutive repeated digits
      B32 increasing = 1;
      B32 repeat = 0;

      // PART II: candidates must have repeated digits in doubles
      Repeat_Record repeats[6] = {0};
      Repeat_Record *curr_repeat = NULL;
      U32 repeat_count = 0;

      S32 last = -1;
      for (U32 d = 0; d < 6; ++d) {
        if ((S32)(digits[d]) < last) {
          increasing = 0;
        }

        if (digits[d] == last) {
          repeat = 1;
          if (curr_repeat == NULL || curr_repeat->digit != digits[d]) {
            curr_repeat = &repeats[repeat_count++];
          }

          if (curr_repeat->run_length == 0) {
            curr_repeat->digit = digits[d];
            curr_repeat->run_length = 2;
          }
          else {
            curr_repeat->run_length++;
          }
        }

        last = digits[d];
      }

      if (increasing && repeat) {
        for (U32 r = 0; r < repeat_count; ++r) {
          if (repeats[r].run_length == 2) {
            matches++;
            break;
          }
        }
      }
    }

    printf("Matches: %u\n", matches);
  }

  return 0;
}
