// 26  Pick the next task  [MEDIUM] [RTOS]
// RTOS, target 20 min. Unit tests call the names below.
//
// A preemptive priority scheduler always runs the highest-priority ready task. Tasks of
// equal priority share the CPU round-robin. Write the scheduler's selection step.
//
// What to write:
//   - A scoped enumeration named TaskState with the values Ready, Blocked and Suspended.
//   - A struct named Task with an int member named priority (a larger number means more
//     important) and a TaskState member named state, declared in that order.
//   - A function named pickNext that takes a pointer to a read-only array of Task, a
//     count of type size_t, and an int lastRun (the index of the task that ran last, or
//     -1 if none has). It returns the index of the ready task with the highest priority.
//     If several ready tasks share that priority, it returns the first of them after
//     lastRun in index order, wrapping around to the start. It returns -1 if no task is
//     ready.
//
// Examples:
//   priorities 1, 3, 2 with states Ready, Blocked, Ready -> 2
//   three Ready tasks at priority 2, lastRun 0 -> 1
//   three Ready tasks at priority 2, lastRun 2 -> 0 (wraps around)
//   every task Blocked or Suspended -> -1
//
// Constraints:
//   - O(n). No heap and no sorting.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

