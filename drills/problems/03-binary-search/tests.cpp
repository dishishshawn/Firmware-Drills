// Tests for this drill. The runner appends this file after answer.cpp.
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cmath>
static void reps_check(const char* name, bool ok, const char* detail) {
    if (ok) std::printf("PASS|%s\n", name);
    else std::printf("FAIL|%s|%s\n", name, detail);
}
static const int reps_unbuffered = (std::setvbuf(stdout, nullptr, _IONBF, 0), 0);
int main() {
    const int a[] = {1, 3, 5, 7, 9};
    reps_check("found in middle", binarySearch(a, 5, 7) == 3, "7 is at index 3");
    reps_check("not present", binarySearch(a, 5, 4) == -1, "4 is not present: -1");
    reps_check("first element", binarySearch(a, 5, 1) == 0, "1 is at index 0");
    reps_check("last element", binarySearch(a, 5, 9) == 4, "9 is at index 4");
    reps_check("empty array", binarySearch(a, 0, 1) == -1, "searching zero elements should return -1");
    reps_check("below range", binarySearch(a, 5, -10) == -1, "-10 is not present: -1");
    reps_check("above range", binarySearch(a, 5, 100) == -1, "100 is not present: -1");
    return 0;
}
