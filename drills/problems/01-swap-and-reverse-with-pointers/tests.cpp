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
    int x = 3, y = 8;
    swapInts(&x, &y);
    reps_check("swap", x == 8 && y == 3, "3 and 8 should become 8 and 3");
    int a[] = {1, 2, 3, 4, 5};
    reverseArray(a, 5);
    reps_check("odd length", a[0] == 5 && a[1] == 4 && a[2] == 3 && a[3] == 2 && a[4] == 1, "1..5 should become 5..1");
    int b[] = {1, 2, 3, 4};
    reverseArray(b, 4);
    reps_check("even length", b[0] == 4 && b[1] == 3 && b[2] == 2 && b[3] == 1, "1..4 should become 4..1");
    int c[] = {42};
    reverseArray(c, 1);
    reps_check("one element", c[0] == 42, "a single element stays put");
    int d[] = {7};
    reverseArray(d, 0);
    reps_check("zero length", d[0] == 7, "length 0 should change nothing");
    return 0;
}
