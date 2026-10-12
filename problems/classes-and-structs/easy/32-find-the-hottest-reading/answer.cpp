// 32  Find the hottest reading  [EASY] [STRUCT]
// Structs, embedded, target 12 min. Unit tests call the names below.
//
// A board polls several temperature sensors and stores each result as a struct. A struct
// can have member functions too, just like a class.
//
// What to write:
//   - A struct named Reading with three members, in this order: sensorId (uint8_t), raw
//     (uint16_t, a 12-bit ADC count from 0 to 4095) and tick (uint32_t, when it was
//     taken).
//   - A member function of Reading named celsius that does not modify the reading and
//     returns raw * 0.1 - 50.0 as a double.
//   - A function named hottest that takes a pointer to a read-only array of Readings and
//     its length (size_t), and returns a const Reading* to the hottest one, or nullptr if
//     the length is 0. On a tie, return the first.
//
// Examples:
//   Reading{1, 750, 100}.celsius() -> 25.0
//   {1, 750, 100}, {2, 900, 101}, {3, 600, 102} -> hottest returns &readings[1]
//   hottest(readings, 0) -> nullptr
//
// Constraints:
//   - Don't copy the array or the winning Reading. Return a pointer into the array.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

#include <cstdint>
#include <cstddef>

struct Reading {

    uint8_t sensorId;
    uint16_t raw;
    uint32_t tick;

    double celsius() const {
        return (double)raw * 0.1 - 50.0;
    };
};

const Reading* hottest(const Reading* readings, size_t length) {

    if(length == 0) { return nullptr; }

    uint16_t hottest = 0;
    size_t index = 0;
    for (size_t i = 0; i < length; i++) {
        if(readings[i].raw > hottest) { hottest = readings[i].raw; index = i; }
    }
    return &readings[index];
}
