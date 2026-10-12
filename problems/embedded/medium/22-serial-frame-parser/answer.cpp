// 22  Serial frame parser  [MEDIUM] [EMBEDDED]
// Embedded, target 25 min. Unit tests call the names below.
//
// A UART receive interrupt hands you one byte at a time. Frames look like this: a start
// byte 0xAA, a length byte (0 to 16), that many payload bytes, then a checksum byte
// equal to the XOR of the length byte and every payload byte.
//
// What to write:
//   - A class named FrameParser. A new parser is waiting for a start byte.
//   - A member function named feed that takes one unsigned 8-bit byte and returns true
//     only when that byte completes a valid frame.
//   - Bytes are ignored until a 0xAA start byte arrives. A length above 16 or a wrong
//     checksum throws the frame away, and the parser goes back to waiting for a start
//     byte. Inside a frame, 0xAA is ordinary data.
//   - Member functions named length (returns size_t) and payload (returns a pointer to
//     read-only unsigned 8-bit bytes) that describe the most recent valid frame. Neither
//     modifies the parser.
//
// Examples:
//   AA 03 01 02 03 03 -> feed returns true on the last byte; length 3, payload 01 02
//     03
//   00 FF AA 01 7E 7F -> garbage before AA is skipped; true on the last byte
//   AA 02 AA 55 FD -> true; payload AA 55
//
// Constraints:
//   - Store the payload in a fixed 16-byte array member. No heap.
//   - Use an enumeration for the parser's states.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

