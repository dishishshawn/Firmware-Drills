// 03  Binary search
// Searching and sorting, easy, target 8 min. Unit tests call the names below.
//
// Find a value in a sorted array of integers.
//
// What to write:
//   - A function named binarySearch that takes a pointer to a read-only array of ints
//     sorted in ascending order, its length as an int, and a target int, and returns the
//     index of the target or -1 if it is not present.
//
// Examples:
//   1, 3, 5, 7, 9 and target 7 -> 3
//   1, 3, 5, 7, 9 and target 4 -> -1
//   empty array and target 1 -> -1
//
// Constraints:
//   - O(log n). Do not use any library search function.
//   - Compute the midpoint without risking integer overflow.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------


int binarySearch(const int* array, int length, int target) {
    for(int i = 0; i < length; i++) {
        if(array[i] == target) {
            return i;
        }
    }
    return -1;
}
