// 14  Sensor class hierarchy
// Classes, inheritance and virtual, medium, target 20 min. Unit tests call the names below.
//
// A data logger reads several kinds of sensors through one interface.
//
// What to write:
//   - An abstract base class named Sensor with a pure virtual member function named read
//     that takes no arguments, returns a double, and does not modify the object. Give it
//     a virtual destructor.
//   - A class named TemperatureSensor derived from Sensor whose constructor takes a raw
//     ADC count as an int (0 to 4095); read returns degrees Celsius as count times 0.1
//     minus 50.
//   - A class named PressureSensor derived from Sensor whose constructor takes
//     kilopascals as a double; read returns them unchanged.
//   - A function named averageReading that takes a read-only reference to a vector of
//     unique_ptr to Sensor and returns the average reading, or 0.0 if the vector is
//     empty.
//
// Examples:
//   TemperatureSensor with count 750 -> read returns 25.0
//   That sensor plus a PressureSensor at 101.3 -> averageReading returns 63.15
//
// Constraints:
//   - Mark the overriding functions so the compiler checks them.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

