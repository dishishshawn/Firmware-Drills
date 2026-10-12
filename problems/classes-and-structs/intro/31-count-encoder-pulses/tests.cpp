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
#include <type_traits>
#include <utility>
static_assert(std::is_same<decltype(std::declval<PulseCounter&>().count()), uint32_t>::value, "count should return uint32_t");
int main() {
    PulseCounter left;
    reps_check("starts at zero", left.count() == 0u, "a new PulseCounter should read 0 (give the member a starting value)");
    left.pulse();
    left.pulse();
    left.pulse();
    reps_check("counts pulses", left.count() == 3u, "3 pulses should count 3");
    PulseCounter right;
    right.pulse();
    reps_check("independent counters", left.count() == 3u && right.count() == 1u, "each counter keeps its own total (a member, not a global)");
    left.reset();
    reps_check("reset", left.count() == 0u && right.count() == 1u, "reset clears only that counter");
    for (int i = 0; i < 100000; ++i) right.pulse();
    reps_check("many pulses", right.count() == 100001u, "100000 more pulses should make 100001");
    const PulseCounter& view = right;
    reps_check("count is const", view.count() == 100001u, "count should work on a const PulseCounter");
    return 0;
}
