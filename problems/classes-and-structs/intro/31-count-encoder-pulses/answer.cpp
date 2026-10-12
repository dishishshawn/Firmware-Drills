// 31  Count encoder pulses  [INTRO] [CLASS]
// Classes, embedded, target 8 min. Unit tests call the names below.
//
// A wheel encoder sends one pulse per slot as the wheel turns. An interrupt calls pulse()
// on every edge and the main loop reads the total. A class keeps the total private, so
// only its own member functions can change it.
//
// What to write:
//   - A class named PulseCounter. A new counter is at 0.
//   - A member function named pulse with no arguments that adds 1.
//   - A member function named count that returns the total as uint32_t and does not
//     modify the counter (mark it const).
//   - A member function named reset that sets the total back to 0.
//
// Examples:
//   PulseCounter left; left.pulse() 3 times -> left.count() is 3
//   left.reset() -> left.count() is 0
//   Two counters are independent: pulsing one does not change the other.
//
// Constraints:
//   - Keep the total in a private member variable. No globals.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------
