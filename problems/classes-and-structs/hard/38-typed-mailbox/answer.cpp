// 38  Typed mailbox  [HARD] [CLASS]
// Class templates, RTOS, target 30 min. Unit tests call the names below.
//
// RTOS queues copy whole messages in and out (FreeRTOS: xQueueSend(q, &msg, 0)). The C
// API takes void* and a byte size, so nothing stops you sending the wrong struct. Write the
// queue as a class template instead: the compiler fixes the message type and the capacity,
// and a Mailbox<SensorMsg, 4> won't accept a MotorCmd.
//
// What to write:
//   - A class template named Mailbox with a type parameter T and a capacity N (size_t):
//       template <typename T, size_t N> class Mailbox
//   - A member function named send that takes a read-only reference to a T, copies it in
//     and returns true, or returns false if the mailbox is full.
//   - A member function named receive that takes a reference to a T. If a message is
//     waiting it copies the oldest one out, removes it and returns true. Otherwise it
//     returns false and leaves the argument alone.
//   - A member function named peek that returns a const T* to the oldest message without
//     removing it, or nullptr if empty.
//   - Member functions named size (size_t), empty and full (bool).
//   - peek, size, empty and full do not modify the mailbox.
//
// Examples:
//   struct SensorMsg { uint8_t id; int16_t value; };
//   Mailbox<SensorMsg, 2> mb;  send({1, 20}), send({2, 30}), send({3, 40}) -> true, true, false
//   SensorMsg m;  mb.receive(m) -> true, m.id is 1, mb.size() is 1
//
// Constraints:
//   - Store the messages in a plain array of N T's inside the object. No heap, no
//     standard containers.
//   - send and receive are O(1): a ring buffer with a head index and a count, no shifting.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------
