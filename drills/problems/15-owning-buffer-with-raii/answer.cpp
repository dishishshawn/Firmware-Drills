// 15  Owning buffer with RAII
// Memory and smart pointers, medium, target 20 min. Checks what your program prints.
//
// A logging module needs a heap buffer whose size is chosen at run time and that frees
// itself automatically.
//
// What to write:
//   - A class that takes a size in bytes in its constructor and owns a heap array of
//     that many bytes through a unique_ptr.
//   - A member function that returns the size, and an indexed read-write accessor for a
//     byte.
//   - Copying the class must be disabled. Moving it must be allowed.
//   - A main that creates a 64-byte buffer, writes 0xAA to index 0, moves the buffer
//     into a second variable, and prints the byte at index 0 of the second variable as
//     an integer on its own line.
//
// Examples:
//   Run the program -> 170
//
// Constraints:
//   - No raw new or delete expressions.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

