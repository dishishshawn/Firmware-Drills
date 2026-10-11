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
    reps_check("set bit 0", setBit(0u, 0u) == 1u, "setBit(0, 0) should be 1");
    reps_check("set bit 31", setBit(0u, 31u) == 0x80000000u, "setBit(0, 31) should be 0x80000000");
    reps_check("set is idempotent", setBit(5u, 0u) == 5u, "setting a bit that is already set changes nothing");
    reps_check("clear bit", clearBit(0xFFu, 3u) == 0xF7u, "clearBit(0xFF, 3) should be 0xF7");
    reps_check("clear bit 31", clearBit(0xFFFFFFFFu, 31u) == 0x7FFFFFFFu, "clearBit(0xFFFFFFFF, 31) should be 0x7FFFFFFF");
    reps_check("toggle off", toggleBit(0xF0u, 4u) == 0xE0u, "toggleBit(0xF0, 4) should be 0xE0");
    reps_check("toggle on", toggleBit(0u, 7u) == 0x80u, "toggleBit(0, 7) should be 0x80");
    reps_check("test bit 31", isBitSet(0x80000000u, 31u) && !isBitSet(0x7FFFFFFFu, 31u), "isBitSet should read bit 31 correctly");
    reps_check("test bit 0", isBitSet(1u, 0u) && !isBitSet(2u, 0u), "isBitSet should read bit 0 correctly");
    return 0;
}
