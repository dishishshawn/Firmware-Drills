// 10  Fixed-size byte queue
// Ring buffers and queues, medium, target 20 min. Unit tests call the names below.
//
// A UART driver needs a first-in, first-out queue of bytes with a fixed capacity and no
// dynamic allocation.
//
// What to write:
//   - A class named ByteQueue that can hold up to 16 bytes in a fixed-size array member.
//     A default-constructed queue is empty.
//   - A member function named push that takes one unsigned 8-bit byte and returns a
//     bool: true if it was stored, false if the queue was full.
//   - A member function named pop that takes a reference to an unsigned 8-bit byte,
//     writes the oldest byte into it, and returns true. If the queue is empty it returns
//     false.
//   - A member function named size that returns how many bytes are stored. It must not
//     modify the object.
//
// Examples:
//   Push 16 bytes into an empty queue -> All 16 pushes return true; the 17th returns
//     false
//   Push 0x01, 0x02, then pop twice -> Pops give 0x01, then 0x02; a third pop returns
//     false
//
// Constraints:
//   - Use head and tail indexes that wrap around.
//   - No heap allocation.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

