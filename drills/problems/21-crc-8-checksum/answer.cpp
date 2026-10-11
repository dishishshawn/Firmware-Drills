// 21  CRC-8 checksum  [MEDIUM] [EMBEDDED]
// Embedded, target 15 min. Unit tests call the names below.
//
// SMBus and many sensor protocols protect each message with CRC-8: polynomial 0x07 (x^8
// + x^2 + x + 1), initial value 0x00, most significant bit first, no final XOR.
//
// What to write:
//   - A function named crc8 that takes a pointer to read-only unsigned 8-bit bytes and a
//     length of type size_t and returns the CRC as an unsigned 8-bit value.
//   - Process each byte bit by bit: XOR the byte into the CRC, then 8 times shift left,
//     XORing with 0x07 whenever the bit shifted out was 1.
//
// Examples:
//   the ASCII bytes of 123456789 -> 0xF4
//   the single byte 0x01 -> 0x07
//   no bytes -> 0x00
//
// Constraints:
//   - No lookup table and no heap. Keep the CRC in an 8-bit variable, or mask it to 8
//     bits after each shift.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

