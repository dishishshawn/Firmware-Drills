// 05  Reverse a linked list
// Linked lists, easy, target 10 min. Unit tests call the names below.
//
// A singly linked list stores integers. Each node holds an integer value and a pointer
// to the next node, or a null pointer at the end.
//
// What to write:
//   - A struct named Node with an int member named value and a pointer-to-Node member
//     named next.
//   - A function named reverseList that takes a pointer to the first node, reverses the
//     list in place, and returns a pointer to the new first node.
//
// Examples:
//   1 -> 2 -> 3 -> 3 -> 2 -> 1
//   An empty list (null pointer) -> A null pointer
//   7 -> 7
//
// Constraints:
//   - O(n) time and O(1) extra memory. Do not allocate new nodes.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

struct Node {
    int value;
    int* pointer;
};

int* reverseList(Node node) {
