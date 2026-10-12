// 35  Task watchdog  [MEDIUM] [CLASS]
// Classes holding structs, RTOS, target 25 min. Unit tests call the names below.
//
// A hardware watchdog resets the chip unless it is kicked in time. With several tasks, a
// monitor kicks it only while every task has checked in recently, so one stuck task still
// causes a reset. Model the monitor's bookkeeping.
//
// What to write:
//   - A class named TaskWatchdog that tracks up to 4 tasks.
//   - A member function named add that takes a timeout in ticks (uint32_t, at least 1) and
//     returns the new task's slot (int: 0, 1, 2, 3 in order), or -1 when all 4 are taken.
//     A new task starts with its full timeout.
//   - A member function named checkIn that takes a slot (int) and resets that task's
//     remaining time to its full timeout. A slot that was never added does nothing.
//   - A member function named tick, called once per system tick, that counts every task
//     down by 1 and returns the lowest slot whose time has run out, or -1 if none has.
//     An expired task stays expired until it checks in.
//
// Examples:
//   add(3) -> 0;  tick, tick, tick -> -1, -1, 0
//   add(3) -> 0;  tick, tick, checkIn(0), tick, tick -> all -1
//   add(5), add(2) -> 0, 1;  tick, tick -> -1, 1
//
// Constraints:
//   - Store each task as a small struct (its timeout and its remaining ticks) in a fixed
//     array of 4 inside the class. No heap.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------
