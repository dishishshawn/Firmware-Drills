// 34  Wake delayed tasks  [MEDIUM] [STRUCT]
// Structs and enums, RTOS, target 20 min. Unit tests call the names below.
//
// An RTOS keeps a task control block (TCB) for every task. When a task calls delay, the
// kernel marks it blocked and records the tick to wake it. On every tick the kernel wakes
// the tasks whose time has come.
//
// What to write:
//   - An enum class named TaskState with the values Ready, Blocked and Suspended.
//   - A struct named Tcb with these members, in this order: id (int), priority (uint8_t),
//     state (TaskState, default Ready) and wakeTick (uint32_t, default 0).
//   - A function named delayTask that takes a Tcb by reference, the current tick and a
//     number of ticks (both uint32_t). It blocks the task and sets wakeTick to now + ticks.
//   - A function named wakeDue that takes a pointer to an array of Tcbs, its length
//     (size_t) and the current tick (uint32_t). Every Blocked task whose wakeTick has been
//     reached becomes Ready. Ready and Suspended tasks are left alone. It returns how many
//     tasks it woke (size_t).
//
// Examples:
//   Tcb t{1, 5};  delayTask(t, 100, 10)  -> state Blocked, wakeTick 110
//   wakeDue(&t, 1, 109) -> 0;  wakeDue(&t, 1, 110) -> 1, state Ready
//
// Constraints:
//   - The tick counter wraps. A task delayed at tick 0xFFFFFFF0 for 0x20 ticks wakes at
//     tick 0x10, not right away. No delay is longer than half the counter range.
//     Drill 19 covers the comparison.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------
