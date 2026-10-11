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
    reps_check("simple elapsed", elapsedTicks(150u, 100u) == 50u, "150 - 100 should be 50");
    reps_check("elapsed across wrap", elapsedTicks(5u, 0xFFFFFFFBu) == 10u, "from 0xFFFFFFFB to 5 is 10 ticks");
    reps_check("no time passed", elapsedTicks(42u, 42u) == 0u, "same tick should be 0 elapsed");
    reps_check("timed out exactly", hasTimedOut(1100u, 100u, 1000u), "1000 ticks elapsed should count as timed out");
    reps_check("not yet", !hasTimedOut(1099u, 100u, 1000u), "999 ticks elapsed is not a timeout");
    reps_check("timeout across wrap", hasTimedOut(500u, 0xFFFFFF00u, 700u), "756 ticks elapsed across the wrap should time out");
    reps_check("no timeout across wrap", !hasTimedOut(200u, 0xFFFFFF00u, 700u), "456 ticks elapsed across the wrap is not a timeout");
    return 0;
}
