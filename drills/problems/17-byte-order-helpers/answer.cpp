// 17  Byte order helpers  [EASY] [EMBEDDED]
// Embedded, target 12 min. Unit tests call the names below.
//
// Sensors and network protocols send multi-byte values in big-endian order, while your
// Cortex-M is little-endian. Write the conversions.
//
// What to write:
//   - A function named swap16 that takes an unsigned 16-bit value and returns it with
//     its two bytes swapped.
//   - A function named swap32 that takes an unsigned 32-bit value and returns it with
//     its byte order reversed.
//   - A function named readBigEndian32 that takes a pointer to 4 read-only unsigned
//     8-bit bytes (most significant byte first) and returns the unsigned 32-bit value.
//   - A function named writeLittleEndian32 that takes a pointer to 4 unsigned 8-bit
//     bytes and an unsigned 32-bit value, writes the value least significant byte first,
//     and returns nothing.
//
// Examples:
//   swap16(0x1234) -> 0x3412
//   swap32(0x12345678) -> 0x78563412
//   readBigEndian32 of DE AD BE EF -> 0xDEADBEEF
//   writeLittleEndian32 of 0x11223344 -> bytes 44 33 22 11
//
// Constraints:
//   - Use shifts and masks. No memcpy, unions, or compiler byte-swap builtins.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

#include <stdint.h>

uint16_t swap16(uint16_t value) {
    uint8_t top = 0;
    uint8_t bottom = 0;
    top = value >> 8; // Isolate the top half
    bottom = value & 0xFF; // Isolate the bottom half
    return ((uint16_t)bottom << 8) | (uint16_t)top;
}

uint32_t swap32(uint32_t value) {
    uint8_t byte0 = 0;
    uint8_t byte1 = 0;
    uint8_t byte2 = 0;
    uint8_t byte3 = 0;
    byte0 = value >> 24; // Isolate the top byte
    byte1 = (value >> 16) & 0xFF; // Isolate the second byte
    byte2 = (value >> 8) & 0xFF; // Isolate the third byte
    byte3 = value & 0xFF; // Isolate the bottom byte
    return ((uint32_t)byte3 << 24) | ((uint32_t)byte2 << 16) | ((uint32_t)byte1 << 8) | (uint32_t)byte0;
}

//   - A function named readBigEndian32 that takes a pointer to 4 read-only unsigned
//     8-bit bytes (most significant byte first) and returns the unsigned 32-bit value.
uint32_t readBigEndian32(const uint8_t* bytes) {
    return ((uint32_t)bytes[0] << 24) | ((uint32_t)bytes[1] << 16) | ((uint32_t)bytes[2] << 8) | bytes[3];
}

//   - A function named writeLittleEndian32 that takes a pointer to 4 unsigned 8-bit
//     bytes (least significant byte first) and a 32-bit value, and writes the value
//     into the bytes in little-endian order.
void writeLittleEndian32(uint8_t* bytes, uint32_t value) {
    bytes[0] = value & 0xFF;
    bytes[1] = (value >> 8) & 0xFF;
    bytes[2] = (value >> 16) & 0xFF;
    bytes[3] = (value >> 24) & 0xFF;
}
