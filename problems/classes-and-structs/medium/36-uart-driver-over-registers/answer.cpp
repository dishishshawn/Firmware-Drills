// 36  UART driver over a register struct  [MEDIUM] [STRUCT] [CLASS]
// Structs and classes, embedded, target 25 min. Unit tests call the names below.
//
// Vendor headers describe a peripheral as a struct laid over its registers' addresses, for
// example #define USART2 ((UartRegs*)0x40004400). A driver class keeps a reference to that
// struct and hides the bit twiddling. The tests pass a UartRegs in ordinary RAM in place
// of the hardware.
//
// What to write:
//   - A struct named UartRegs with four volatile uint32_t members, in this order: SR
//     (status), DR (data), BRR (baud rate) and CR1 (control). Nothing else, so each one
//     sits 4 bytes after the last, like the real registers.
//   - A class named Uart whose constructor takes a UartRegs by reference and keeps the
//     reference (not a copy).
//   - A member function named init that takes the peripheral clock and the baud rate (both
//     uint32_t). It sets BRR to clock / baud rounded to the nearest integer, then sets CR1
//     to UE | TE | RE (bits 13, 3 and 2).
//   - A member function named write that takes a byte (uint8_t). If SR's TXE bit (bit 7)
//     is set, it stores the byte in DR and returns true. Otherwise it returns false and
//     leaves DR alone.
//   - A member function named read that takes a reference to a uint8_t. If SR's RXNE bit
//     (bit 5) is set, it stores the low 8 bits of DR there and returns true. Otherwise it
//     returns false.
//
// Examples:
//   init(16000000, 115200) -> BRR 139 (138.89 rounds up), CR1 0x200C
//   SR = 0x80; write(0x41) -> true, DR 0x41
//   SR = 0;    write(0x41) -> false
//
// Constraints:
//   - Name the bits (constexpr uint32_t kTxe = 1u << 7; and so on) instead of writing
//     magic numbers in the logic.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------
