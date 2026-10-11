// 04  XOR checksum
// Embedded data and CAN frames, easy, target 10 min. Unit tests call the names below.
//
// A serial protocol ends each packet with one checksum byte: the XOR of every byte
// before it.
//
// What to write:
//   - A function named xorChecksum that takes a pointer to read-only unsigned 8-bit
//     bytes and a length of type size_t and returns the 8-bit XOR of all of them as an
//     unsigned 8-bit value.
//   - A function named isValidPacket that takes the same two arguments and returns true
//     if the last byte equals the XOR of all the bytes before it. Packets shorter than 2
//     bytes are invalid.
//
// Examples:
//   xorChecksum of 0x12, 0x34 -> 0x26
//   isValidPacket of 0x12, 0x34, 0x26 -> true
//   isValidPacket of 0x12, 0x34, 0x27 -> false
//
// Constraints:
//   - No dynamic allocation.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdint.h>

// Return the XOR of a byte
uint8_t xorChecksum(const uint8_t* Byte, size_t length) {
    uint8_t Xor = 0;
    for(size_t i = 0; i < length; i++) {
        Xor ^= Byte[i];
    }
    return Xor;
}

int isValidPacket(const uint8_t* Byte, size_t length) {
    if(length < 2) {
        return false;
    }
    return xorChecksum(Byte, length - 1) == Byte[length - 1];
}
