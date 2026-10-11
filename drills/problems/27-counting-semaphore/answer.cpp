// 27  Counting semaphore  [MEDIUM] [RTOS]
// RTOS, target 20 min. Unit tests call the names below.
//
// A counting semaphore guards a pool of identical resources, such as 2 DMA channels.
// Model its bookkeeping: the count, and a first-in, first-out list of tasks waiting for
// it.
//
// What to write:
//   - A class named CountingSemaphore whose constructor takes an initial count and a
//     maximum count (both unsigned int).
//   - A member function named tryTake that takes a task id (int). If the count is above
//     zero it decrements the count and returns true. Otherwise it adds the id to the end
//     of the wait list (which holds up to 8 ids; when full, the id is not added) and
//     returns false.
//   - A member function named give with no arguments. If any task is waiting, it removes
//     the first waiter and returns its id: that task now holds the resource, so the
//     count does not change. Otherwise it increments the count, but never past the
//     maximum, and returns -1.
//   - Member functions named count (returns unsigned int) and waiting (returns size_t,
//     the number of waiting tasks). Neither modifies the semaphore.
//
// Examples:
//   CountingSemaphore(2, 2); tryTake(1), tryTake(2), tryTake(3) -> true, true, false;
//     count 0, waiting 1
//   then give() -> 3 (task 3 gets the resource)
//   give() with nobody waiting at the maximum count -> -1, count stays at the maximum
//
// Constraints:
//   - Fixed-size array for the wait list. No heap, no standard containers.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

