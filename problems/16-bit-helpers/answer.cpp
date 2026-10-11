// 16  Bit helpers  [EASY] [EMBEDDED]
// Embedded, target 8 min. Unit tests call the names below.
//
// Firmware sets, clears and tests single bits in 32-bit registers all day. Write the
// four helpers every driver ends up needing.
//
// What to write:
//   - Functions named setBit, clearBit and toggleBit. Each takes a register value
//     (unsigned 32-bit) and a bit number (unsigned int, 0 to 31) and returns the new
//     register value as an unsigned 32-bit value.
//   - A function named isBitSet that takes a register value and a bit number and returns
//     a bool.
//
// Examples:
//   setBit(0x00000000, 31) -> 0x80000000 (turns the 31st bit on)
//   clearBit(0xFF, 3) -> 0xF7
//   toggleBit(0xF0, 4) -> 0xE0
//   isBitSet(0x7FFFFFFF, 31) -> false
//
// Constraints:
//   - Bit 31 must work without undefined behavior: shift an unsigned 1, not a plain int
//     1.
//   - No std::bitset.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

#include <stdint.h>

uint32_t setBit(uint32_t Bit, int Number) {
    Bit |= (1 << Number);
    return Bit;
}

uint32_t clearBit(uint32_t Bit, int Number) {
    Bit &= ~(1 << Number);
    return Bit;
}

uint32_t toggleBit(uint32_t Bit, int Number) {
    Bit ^= (1 << Number);
    return Bit;
}

int isBitSet(uint32_t Bit, int Number) {
    return (Bit >> Number) & 1;
}
