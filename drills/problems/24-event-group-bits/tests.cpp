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
    EventGroup g;
    reps_check("starts empty", g.getBits() == 0u, "a new event group has no bits set");
    g.setBits(0x5u);
    reps_check("set bits", g.getBits() == 0x5u, "setBits(0x5) should give 0x5");
    reps_check("wait all true", g.waitAll(0x5u, false), "waitAll(0x5) with 0x5 set should be true");
    reps_check("wait all false", !g.waitAll(0x7u, false), "waitAll(0x7) with only 0x5 set should be false");
    reps_check("wait any true", g.waitAny(0x6u, false), "waitAny(0x6) with bit 2 set should be true");
    reps_check("wait any false", !g.waitAny(0x8u, false), "waitAny(0x8) with bit 3 clear should be false");
    reps_check("no clear without flag", g.getBits() == 0x5u, "checks with clearOnExit false must not change the bits");
    reps_check("wait all and clear", g.waitAll(0x1u, true) && g.getBits() == 0x4u, "waitAll(0x1, true) should clear bit 0, leaving 0x4");
    g.setBits(0x8u);
    reps_check("wait any clears only matching set bits", g.waitAny(0xCu, true) && g.getBits() == 0x0u, "waitAny(0xC, true) should clear bits 2 and 3");
    g.setBits(0xFu); g.clearBits(0x3u);
    reps_check("clear bits", g.getBits() == 0xCu, "clearBits(0x3) on 0xF should leave 0xC");
    reps_check("failed wait does not clear", !g.waitAll(0x3u, true) && g.getBits() == 0xCu, "a wait that returns false must not clear anything");
    return 0;
}
