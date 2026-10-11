// 23  Software timer  [EASY] [RTOS]
// RTOS, target 12 min. Unit tests call the names below.
//
// An RTOS timer service counts system ticks and fires callbacks. Model one
// timer: it can be one-shot or periodic.
//
// What to write:
//   - A class named SoftTimer. A new timer is stopped.
//   - A member function named start that takes a period in ticks (unsigned
//   32-bit, at
//     least 1) and a bool that says whether it repeats, and arms the timer.
//     Starting a running timer restarts its count.
//   - A member function named stop that disarms it.
//   - A member function named tick, called once per system tick, that returns
//   true on
//     the tick the timer expires: exactly period ticks after start. A one-shot
//     timer stops after it fires. A periodic timer reloads and fires every
//     period ticks.
//   - A member function named isRunning that returns a bool and does not modify
//   the
//     timer.
//
// Examples:
//   start(3, false), then tick 5 times -> false, false, true, false, false
//   start(2, true), then tick 6 times -> false, true, false, true, false, true
//   start(2, true), tick once, stop, tick 3 times -> never fires
//
// Constraints:
//   - O(1) per tick. No heap.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a
// task, alt-t reruns it).
// --------------------------------------------------------------------------------------

// tick() -> counter++
// counter % count -> true
// reset counter to zero ON the tick it updates
// repeat if true

#include <stdint.h>

class SoftTimer {
public:
  void start(uint32_t period, bool repeated) {
    period_ = period;
    repeated_ = repeated;
    counter_ = 0; // starting a running timer restarts its count
    running_ = true;
  }

  void stop() { running_ = false; }

  bool tick() {
    if (!running_) {
      return false;
    }
    counter_++;
    if (counter_ % period_ == 0) {
      counter_ = 0; // reset on the tick it fires, so it never wraps
      if (!repeated_) {
        running_ = false; // one-shot: wait for the next start
      }
      return true;
    }
    return false;
  }

  bool isRunning() const { return running_; }

private:
  uint32_t period_ = 0;
  bool repeated_ = false;
  uint32_t counter_ = 0;
  bool running_ = false;
};
