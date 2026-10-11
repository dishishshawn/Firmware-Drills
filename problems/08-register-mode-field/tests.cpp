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
    reps_check("shift constant", MODE_SHIFT == 4u, "MODE_SHIFT should be 4");
    reps_check("mask constant", MODE_MASK == 0x70u, "MODE_MASK should be 0x70");
    reps_check("read mode", getMode(0x00000050u) == 5u, "getMode(0x50) should be 5");
    reps_check("write into all ones", setMode(0xFFFFFFFFu, 2u) == 0xFFFFFFAFu, "setMode(0xFFFFFFFF, 2) should be 0xFFFFFFAF");
    reps_check("write into zero", setMode(0u, 7u) == 0x70u, "setMode(0, 7) should be 0x70");
    reps_check("mode wider than 3 bits", setMode(0u, 9u) == 0x10u, "setMode(0, 9) should use only the low 3 bits: 0x10");
    reps_check("other bits preserved", setMode(0x12345678u, 3u) == 0x12345638u, "setMode(0x12345678, 3) should be 0x12345638");
    return 0;
}
