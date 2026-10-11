// 20  Button debouncer  [MEDIUM] [EMBEDDED]
// Embedded, target 20 min. Unit tests call the names below.
//
// A mechanical button bounces for a few milliseconds when pressed or released. A 1 ms
// timer interrupt samples the raw pin, and the debouncer decides what the button is
// really doing.
//
// What to write:
//   - A class named Debouncer whose constructor takes the number of consecutive samples
//     required, as an unsigned int (at least 1). A new Debouncer reports released
//     (false).
//   - A member function named update that takes the raw pin reading as a bool and
//     returns the debounced state as a bool. The debounced state changes only after the
//     raw reading has differed from it for the required number of consecutive samples.
//     Any sample equal to the current debounced state resets that count.
//   - A member function named pressedEvent with no arguments that returns true once
//     after each released-to-pressed change, then false until the next press.
//
// Examples:
//   Debouncer(3), raw true, true, true -> update returns false, false, true
//   Debouncer(3), raw true, false, true, true, true -> false until the last sample,
//     which returns true
//   pressedEvent after that press, called twice -> true, then false
//
// Constraints:
//   - No heap allocation. O(1) work per sample.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

