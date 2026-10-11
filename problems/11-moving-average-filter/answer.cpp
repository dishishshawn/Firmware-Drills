// 11  Moving average filter
// Ring buffers and queues, medium, target 20 min. Unit tests call the names below.
//
// A sensor driver smooths noisy readings by averaging the most recent 8 samples.
//
// What to write:
//   - A class named MovingAverage that stores up to 8 signed 16-bit samples in a fixed
//     array. A default-constructed object has no samples.
//   - A member function named add that takes one signed 16-bit sample. Once 8 are
//     stored, a new sample overwrites the oldest.
//   - A member function named average that returns the average of the stored samples as
//     a double. Before 8 samples arrive it averages only the ones received. With no
//     samples it returns 0.0. It must not modify the object.
//
// Examples:
//   add 10, then add 20 -> average is 15.0
//   add 100 eight times, then add 0 -> average is 87.5
//
// Constraints:
//   - Keep a running sum so adding a sample is O(1).
//   - The running sum must not overflow for the full range of 16-bit samples.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

