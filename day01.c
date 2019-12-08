#if 0
#!/ usr / bin / env bash

set -e

if [ ! -d "build" ]; then
  mkdir build
fi

#args="100756"
args="140517 61738 141916 78376 69208 131761 67212 137805 79089 100457 108707 75235 51118 149457 68888 85722 91418 74481 93441 124911 75441 101542 149092 83149 139256 83398 76398 132252 137763 142758 136279 126238 102888 108723 119982 65216 61412 120894 118761 100221 67132 115494 95623 52819 78612 125505 80523 97774 67569 114514 131671 149811 77679 65540 98415 60595 105589 81927 60249 62514 139506 149532 146885 148831 142896 106300 106313 101456 96521 67104 142037 128258 128769 135081 93181 50735 147720 73775 58113 53478 96705 122060 135329 121513 54539 62404 66334 116924 90977 135383 51479 87581 124040 64048 78616 128068 148184 71714 58847 84640"

clang -std=gnu11 -g day01.c -o build/day01

build/day01 $args

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

S32 main(S32 argc, char **argv) {
  U64 total_fuel = 0ull;

  // PART I: fuel needed for the modules

  for (S32 i = 1; i < argc; ++i) {
    char *arg = argv[i];
    U32 mass = strtoul(arg, NULL, 10);

    U32 fuel = mass / 3 - 2;

    // PART II: fuel needed for the fuel's mass
    S32 fuel_mass = (S32)fuel;
    do {
      S32 add_fuel = fuel_mass / 3 - 2;
      fuel_mass = add_fuel > 0 ? add_fuel : 0;
      total_fuel += (U32)fuel_mass;
    } while (fuel_mass > 0);

    total_fuel += fuel;
  }

  printf("Total fuel: %llu\n", total_fuel);

  return 0;
}
