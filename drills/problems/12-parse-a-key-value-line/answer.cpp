// 12  Parse a key=value line
// Strings and parsing, medium, target 15 min. Unit tests call the names below.
//
// A configuration file has lines of the form key=value where the value is a decimal
// integer that may be negative.
//
// What to write:
//   - A function named parseKeyValue that takes the line as a read-only reference to a
//     standard string, a reference to a standard string for the key, and a reference to
//     an int for the value.
//   - It returns true and fills both outputs on success. It returns false if there is no
//     equals sign, the key is empty, the value is empty, or the value contains anything
//     other than an optional leading minus sign followed by at least one digit.
//
// Examples:
//   speed=1500 -> true, key speed, value 1500
//   temp=-5 -> true, key temp, value -5
//   =4 -> false
//   mode=fast -> false
//
// Constraints:
//   - Do not use exceptions or library number parsers. Convert the digits yourself.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

