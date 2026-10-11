// 06  Distinct words in order
// STL containers, easy, target 10 min. Unit tests call the names below.
//
// Given one line of text, report each distinct word once, in the order it first appears.
//
// What to write:
//   - A function named distinctWords that takes the line as a read-only reference to a
//     standard string and returns a vector of standard strings holding the distinct
//     words in first-seen order.
//   - Words are separated by one or more spaces. Comparison is case-sensitive.
//
// Examples:
//   the cat and the hat -> the, cat, and, hat
//   a a A -> a, A
//   an empty string -> an empty vector
//
// Constraints:
//   - Average O(n) time in the length of the text: use a hash set to remember words
//     already seen.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

