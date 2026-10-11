// 19  Tick counter wraparound  [EASY] [EMBEDDED]
// Embedded, target 8 min. Unit tests call the names below.
//
// A 32-bit millisecond tick counter wraps to 0 after about 49.7 days. Timeout checks
// have to keep working across that wrap.
//
// What to write:
//   - A function named elapsedTicks that takes the current tick and a start tick (both
//     unsigned 32-bit) and returns the ticks elapsed since start as an unsigned 32-bit
//     value, correct even if the counter wrapped once in between.
//   - A function named hasTimedOut that takes now, start and a timeout (all unsigned
//     32-bit) and returns true when at least timeout ticks have elapsed.
//
// Examples:
//   elapsedTicks(150, 100) -> 50
//   elapsedTicks(5, 0xFFFFFFFB) -> 10
//   hasTimedOut(1100, 100, 1000) -> true
//   hasTimedOut(200, 0xFFFFFF00, 700) -> false (456 elapsed)
//
// Constraints:
//   - No 64-bit types and no special-casing the wrap: unsigned subtraction already
//     handles it.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

