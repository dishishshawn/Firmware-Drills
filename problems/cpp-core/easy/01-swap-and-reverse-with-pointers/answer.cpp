// 01  Swap and reverse with pointers
// Pointers and arrays, easy, target 10 min. Unit tests call the names below.
//
// Practice passing addresses: swap two integers through pointers, then use that swap to
// reverse an array in place.
//
// What to write:
//   - A function named swapInts that takes two pointers to int and exchanges the values
//     they point to. It returns nothing.
//   - A function named reverseArray that takes a pointer to int and a length of type
//     size_t and reverses the array in place by calling swapInts.
//
// Examples:
//   swapInts on 3 and 8 -> the values become 8 and 3
//   reverseArray on 1, 2, 3, 4, 5 -> 5, 4, 3, 2, 1
//   reverseArray with length 0 -> nothing changes
//
// Constraints:
//   - No standard library functions. Walk two pointers or two indexes toward the middle.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

#include <stddef.h>

void swapInts(int* first, int* second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

void reverseArray(int* array, size_t length) {
    // Reverse the array in place by calling SwapInt
    for(size_t i = 0; i < length / 2; i++) {
        swapInts(&array[i], &array[length - 1 - i]);
    }
}
