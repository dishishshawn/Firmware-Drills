// 28  ISR-to-task message queue  [MEDIUM] [RTOS]
// RTOS, target 20 min. Unit tests call the names below.
//
// An interrupt must never block, so when the queue to its task is full it drops the
// message and counts the loss. Write the queue as a class template so one implementation
// serves bytes, CAN frames, or anything else.
//
// What to write:
//   - A class template named MessageQueue with a type parameter for the message type and
//     a size_t non-type parameter N for the capacity. Messages are stored by value in a
//     fixed array.
//   - A member function named sendFromIsr that takes a message by read-only reference
//     and returns a bool. It never blocks: when the queue already holds N messages it
//     returns false and increments a dropped counter.
//   - A member function named receive that takes a reference to a message, copies the
//     oldest message into it, removes it, and returns true. It returns false when the
//     queue is empty.
//   - Member functions named size and dropped that return size_t and do not modify the
//     queue.
//
// Examples:
//   MessageQueue of int with N 4; send 1 to 5 -> first 4 sends return true, the 5th
//     false; dropped() is 1
//   then receive 4 times -> 1, 2, 3, 4
//   receive on an empty queue -> false
//
// Constraints:
//   - No heap and no standard containers. The queue must hold N messages, not N - 1.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

