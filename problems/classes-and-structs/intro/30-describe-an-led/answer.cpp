// 30  Describe an LED  [INTRO] [STRUCT]
// Structs, embedded, target 5 min. Unit tests call the names below.
//
// A struct bundles related values into one type. A board has several LEDs, and each one
// is a GPIO pin number plus whether it is lit.
//
// What to write:
//   - A struct named Led with two members, in this order: pin (uint8_t) and on (bool).
//     A new Led is off, so give on a default value of false.
//   - A function named turnOn that takes a Led by reference and lights it.
//   - A function named toggle that takes a Led by reference and flips it.
//   - A function named isLit that takes a read-only reference to a Led and returns on.
//
// Examples:
//   Led status{13};       -> status.pin is 13, status.on is false
//   turnOn(status);       -> status.on is true
//   toggle(status) twice  -> back where it started
//
// Constraints:
//   - Include <cstdint> for uint8_t.
//   - Struct members are public: the functions reach them with a dot, as in led.on.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

struct Led {
    uint8_t pin;
    bool on;
};
