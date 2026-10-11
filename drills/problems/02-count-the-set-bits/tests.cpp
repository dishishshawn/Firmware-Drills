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
    reps_check("zero", countSetBits(0u) == 0, "expected 0");
    reps_check("eleven", countSetBits(11u) == 3, "expected 3 for 11");
    reps_check("all ones", countSetBits(0xFFFFFFFFu) == 32, "expected 32 for 0xFFFFFFFF");
    reps_check("top bit only", countSetBits(0x80000000u) == 1, "expected 1 for 0x80000000");
    reps_check("alternating", countSetBits(0x55555555u) == 16, "expected 16 for 0x55555555");
    return 0;
}
