// 29  Mutex with priority inheritance  [MEDIUM] [RTOS]
// RTOS, target 25 min. Unit tests call the names below.
//
// Priority inversion: a low-priority task holds a mutex, a high-priority task waits for
// it, and a medium-priority task preempts the low one, so the high one waits
// indefinitely. Priority inheritance fixes it by temporarily raising the holder to the
// priority of its most important waiter. Model one such mutex.
//
// What to write:
//   - A struct named Task with int members named id, basePriority and priority, declared
//     in that order. priority is the effective priority and starts equal to
//     basePriority. A larger number means more important.
//   - A class named PiMutex. A new mutex is free.
//   - A member function named lock that takes a reference to a Task. If the mutex is
//     free, that task becomes the owner and lock returns true. Otherwise the task joins
//     the wait list (up to 8 tasks) and lock returns false; if the waiter's priority is
//     above the owner's priority, raise the owner's priority to match.
//   - A member function named unlock that takes a reference to a Task and returns a
//     pointer to Task. If the task is not the owner, nothing changes and it returns a
//     null pointer. Otherwise it restores the owner's priority to its basePriority,
//     hands the mutex to the waiting task with the highest priority (the earliest waiter
//     on a tie), removes it from the wait list and returns a pointer to it. With no
//     waiters the mutex becomes free and unlock returns a null pointer.
//   - A member function named owner that returns a pointer to the owning Task (null when
//     free) and does not modify the mutex.
//
// Examples:
//   low (priority 1) locks; high (priority 3) tries to lock -> low's priority becomes
//     3; high waits
//   low unlocks -> low's priority returns to 1; returns a pointer to high, which now
//     owns the mutex
//   a task that doesn't own the mutex calls unlock -> null pointer; nothing changes
//
// Constraints:
//   - Store Task pointers in a fixed array. No heap, no standard containers.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

