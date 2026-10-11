// 13  Motor controller states
// State machines, medium, target 15 min. Checks what your program prints.
//
// A motor controller has three states: Idle, Running, and Fault. It reacts to four
// events: Start, Stop, EStop, and Reset.
//
// What to write:
//   - A scoped enumeration for the states and one for the events.
//   - A function that takes the current state and an event and returns the next state.
//     Rules: Idle plus Start goes to Running. Running plus Stop goes to Idle. EStop from
//     any state goes to Fault. Fault plus Reset goes to Idle. Every other combination
//     leaves the state unchanged.
//   - A function that returns a state's name as text: Idle, Running, or Fault.
//   - A main that starts in Idle, applies Start, Stop, Start, EStop, Start, Reset in
//     order, and prints the state name after each event on its own line.
//
// Examples:
//   Run the program -> Running, Idle, Running, Fault, Fault, Idle, one per line
//
// Constraints:
//   - Use a switch statement in the transition function.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

