// 37  Critical section guard  [HARD] [CLASS]
// Classes, constructors and destructors (RAII), RTOS, target 25 min. Unit tests call the
// names below.
//
// Data shared with an interrupt handler must be changed with interrupts off. Turning them
// back on by hand breaks on an early return, and an inner section that turns them on ends
// the outer one too soon. A guard object fixes both: its constructor saves the interrupt
// state and disables interrupts, and its destructor restores the saved state when the
// object goes out of scope, however the scope is left.
//
// The "hardware" is given below the line: irqSave() disables interrupts and returns
// whether they were on; irqRestore(was) puts that state back. They stand in for PRIMASK on
// a Cortex-M. Don't change them.
//
// What to write:
//   - A class named CriticalSection. Its constructor takes no arguments, calls irqSave and
//     keeps the result. Its destructor calls irqRestore with that saved value.
//   - Copying or assigning a CriticalSection must not compile, because two copies would
//     restore twice. Delete the copy constructor and the copy assignment operator.
//   - A function named claimSlot that takes a reference to a uint32_t count of used slots
//     (shared with an ISR) and a limit (uint32_t), and returns bool. Inside one
//     CriticalSection: if the count has reached the limit, return false right away;
//     otherwise add 1 and return true.
//
// Examples:
//   interrupts on; { CriticalSection a; { CriticalSection b; } }
//     -> still off after b ends, back on after a ends
//   interrupts already off (inside an ISR); { CriticalSection c; } -> still off afterwards
//   used 2, limit 2: claimSlot(used, 2) -> false, used stays 2, interrupts back on
//
// Constraints:
//   - Each object keeps its own saved state. No extra globals.
//   - CriticalSection(); on its own line makes a temporary that is destroyed at the
//     semicolon. Give the object a name: CriticalSection cs;
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

// Given: the "hardware". Don't change it.
#include <cstdint>

bool g_irqEnabled = true;
unsigned g_irqSaves = 0;  // lets the tests count your irqSave calls

bool irqSave() {
    ++g_irqSaves;
    bool was = g_irqEnabled;
    g_irqEnabled = false;
    return was;
}

void irqRestore(bool was) { g_irqEnabled = was; }

// Your code below.
