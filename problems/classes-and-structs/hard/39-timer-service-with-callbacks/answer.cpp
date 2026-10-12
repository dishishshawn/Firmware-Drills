// 39  Timer service with callbacks  [HARD] [CLASS] [STRUCT]
// Classes, structs and function pointers, RTOS, target 35 min. Unit tests call the names
// below.
//
// Drill 23 modelled one timer. An RTOS timer service owns many and calls a function when
// each one expires, like FreeRTOS xTimerCreate. The callback is a plain function pointer
// plus a void* context, which is how C APIs tell a callback which object it is for.
//
// What to write:
//   - A type alias:  using TimerCallback = void (*)(void* context);
//   - A class named TimerService with room for 8 timers.
//   - A member function named create that takes a period in ticks (uint32_t, at least 1),
//     a bool that says whether it repeats, a TimerCallback (never null) and a void*
//     context. It starts the timer in the lowest free slot and returns that slot as a
//     handle (int, 0 to 7), or -1 if all 8 are in use.
//   - A member function named cancel that takes a handle, frees that slot and returns
//     true. A handle that is out of range or not in use returns false.
//   - A member function named tick, called once per system tick. Every timer in use counts
//     down, and each one that expires (period ticks after create, or after its last
//     firing) calls its callback with its context, in handle order. A one-shot timer frees
//     its slot when it fires; a periodic one reloads. tick returns how many callbacks it
//     made (size_t).
//   - A member function named active that returns how many slots are in use (size_t) and
//     does not modify the service.
//
// Examples:
//   create(2, false, cb, &x) -> 0;  tick -> 0;  tick -> 1 (cb(&x) ran);  active() -> 0
//   create(3, true, cb, &x);  9 ticks -> cb ran 3 times
//
// Constraints:
//   - A fixed array of 8 timer structs inside the class. No heap, no std::function.
//   - A callback may cancel its own timer. It must not fire again after that.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------
