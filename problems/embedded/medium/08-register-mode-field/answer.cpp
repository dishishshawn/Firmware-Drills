// 08  Register mode field
// Bit manipulation and registers, medium, target 15 min. Unit tests call the names below.
//
// A peripheral's 32-bit control register holds a 3-bit mode field in bits 4 through 6
// (bit 0 is the least significant bit).
//
// What to write:
//   - Two compile-time constants: MODE_SHIFT, the field's shift amount, and MODE_MASK,
//     the field's mask already shifted into place. Both unsigned 32-bit.
//   - A function named getMode that takes a register value (unsigned 32-bit) and returns
//     the mode field as an unsigned 32-bit value from 0 to 7.
//   - A function named setMode that takes a register value and a new mode (both unsigned
//     32-bit) and returns the register value with only those three bits replaced. Every
//     other bit must be unchanged.
//
// Examples:
//   getMode of 0x00000050 -> 5
//   setMode of 0xFFFFFFFF with mode 2 -> 0xFFFFFFAF
//   setMode of 0x00000000 with mode 7 -> 0x00000070
//
// Constraints:
//   - If the new mode is larger than 7, only its low 3 bits are used.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

