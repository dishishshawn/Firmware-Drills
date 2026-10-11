// 24  Event group bits  [EASY] [RTOS]
// RTOS, target 12 min. Unit tests call the names below.
//
// An event group lets tasks wait on several flags at once, like 'GPS fix ready' and 'IMU
// calibrated'. Model the non-blocking check a task makes before it would block.
//
// What to write:
//   - A class named EventGroup. A new group has no bits set.
//   - Member functions named setBits and clearBits that take an unsigned 32-bit mask and
//     return nothing, and getBits, which returns the current bits as an unsigned 32-bit
//     value without modifying the group.
//   - A member function named waitAll that takes a mask and a bool clearOnExit and
//     returns true if every bit in the mask is set. If it returns true and clearOnExit
//     is true, it clears the bits in the mask.
//   - A member function named waitAny with the same parameters that returns true if at
//     least one bit in the mask is set. If it returns true and clearOnExit is true, it
//     clears the bits of the mask that were set.
//
// Examples:
//   setBits(0x5), waitAll(0x5, false) -> true
//   setBits(0x5), waitAll(0x7, false) -> false
//   setBits(0x5), waitAny(0x6, false) -> true
//   setBits(0x5), waitAll(0x1, true), getBits() -> true, then 0x4
//
// Constraints:
//   - Bit operations only. No containers.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------
