// 02  Count the set bits
// Bit manipulation and registers, easy, target 8 min. Unit tests call the names below.
//
// A diagnostic routine needs to know how many bits are set in a 32-bit status word.
//
// What to write:
//   - A function named countSetBits that takes an unsigned 32-bit integer and returns,
//     as an int, the number of bits that are 1.
//   - Do not use any compiler builtin or library function that counts bits.
//
// Examples:
//   0 -> 0
//   11 (binary 1011) -> 3
//   4294967295 (all 32 bits set) -> 32
//
// Constraints:
//   - Must work for every 32-bit value, including 0 and all ones.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

#include <stdint.h>

int countSetBits(uint32_t Set) {
    int count = 0;
    for(int i = 0; i < 32; i++) {
        if(Set >> i & 1U) {
            count++;
        }
    }
    return count;
}
