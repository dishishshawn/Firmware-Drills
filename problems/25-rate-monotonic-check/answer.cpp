// 25  Rate monotonic check  [EASY] [RTOS]
// RTOS, target 12 min. Unit tests call the names below.
//
// Under rate monotonic scheduling, the task with the shortest period gets the highest
// priority. Liu and Layland showed n periodic tasks always meet their deadlines if total
// CPU utilization is at most n times (2 to the power 1/n, minus 1). The test is
// sufficient but not necessary: a task set above the bound might still be schedulable.
//
// What to write:
//   - A function named utilization that takes a pointer to read-only worst-case
//     execution times, a pointer to read-only periods (both unsigned 32-bit, same
//     units), and a count of type size_t, and returns the total utilization (sum of time
//     divided by period) as a double.
//   - A function named rmsSchedulable with the same parameters that returns true when
//     the utilization is at most the Liu and Layland bound for that many tasks. It
//     returns true for zero tasks.
//
// Examples:
//   times 1, 1, 2 with periods 4, 5, 10 -> utilization 0.65; bound for 3 tasks is
//     about 0.780; schedulable
//   times 1, 1 with periods 2, 3 -> utilization 0.833; bound for 2 tasks is about
//     0.828; not schedulable
//   time 1 with period 1 -> utilization 1.0; bound for 1 task is 1.0; schedulable
//
// Constraints:
//   - Watch for integer division: convert to double before dividing.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

