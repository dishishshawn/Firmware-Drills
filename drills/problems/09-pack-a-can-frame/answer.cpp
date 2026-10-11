// 09  Pack a CAN frame
// Embedded data and CAN frames, medium, target 20 min. Unit tests call the names below.
//
// A CAN frame carries an 11-bit identifier, a data length from 0 to 8, and up to 8 data
// bytes. A motor controller reports its speed and temperature in one frame.
//
// What to write:
//   - A struct named CanFrame with an unsigned 32-bit member named id, an unsigned 8-bit
//     member named len, and an array of 8 unsigned 8-bit bytes named data.
//   - A function named packMotorStatus that takes an unsigned 16-bit speed and a signed
//     8-bit temperature and returns a CanFrame with id 0x123, len 3, the speed in data
//     bytes 0 and 1 little-endian (low byte first), and the temperature in byte 2.
//   - A function named unpackMotorStatus that takes a read-only reference to a CanFrame
//     plus a reference to an unsigned 16-bit speed and a reference to a signed 8-bit
//     temperature. It returns false, leaving both outputs untouched, if id is not 0x123
//     or len is not 3. Otherwise it fills both outputs and returns true.
//
// Examples:
//   packMotorStatus with speed 1500, temperature -5 -> id 0x123, len 3, data 0xDC 0x05
//     0xFB
//   unpackMotorStatus of that frame -> true, speed 1500, temperature -5
//   unpackMotorStatus of a frame with id 0x124 -> false
//
// Constraints:
//   - Use bit shifts and masks, not memcpy, to place the speed bytes.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

