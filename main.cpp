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
