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
    PwmChannel ch(1000);
    reps_check("starts at 0%", ch.duty() == 0 && ch.compare() == 0u, "a new channel should have 0% duty");
    ch.setDuty(25);
    reps_check("25 percent", ch.duty() == 25 && ch.compare() == 250u, "25% of 1000 is 250");
    ch.setDuty(150);
    reps_check("clamp high", ch.duty() == 100 && ch.compare() == 1000u, "150% should clamp to 100%");
    ch.setDuty(-5);
    reps_check("clamp low", ch.duty() == 0 && ch.compare() == 0u, "-5% should clamp to 0%");
    PwmChannel odd(999);
    odd.setDuty(50);
    reps_check("rounds down", odd.compare() == 499u, "50% of 999 is 499.5, rounded down to 499");
    reps_check("separate channels", ch.duty() == 0 && odd.duty() == 50, "each channel keeps its own duty");
    PwmChannel big(4000000000u);
    big.setDuty(100);
    reps_check("no overflow", big.compare() == 4000000000u, "4000000000 * 100 doesn't fit in 32 bits; widen to uint64_t before multiplying");
    big.setDuty(33);
    reps_check("no overflow at 33%", big.compare() == 1320000000u, "33% of 4000000000 is 1320000000");
    const PwmChannel& view = odd;
    reps_check("const accessors", view.duty() == 50 && view.compare() == 499u, "duty and compare should work on a const channel");
    return 0;
}
