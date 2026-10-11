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
    const uint32_t c1[] = {1, 1, 2}; const uint32_t t1[] = {4, 5, 10};
    reps_check("utilization", std::fabs(utilization(c1, t1, 3) - 0.65) < 1e-9, "1/4 + 1/5 + 2/10 should be 0.65");
    reps_check("three tasks pass", rmsSchedulable(c1, t1, 3), "0.65 is under the 3-task bound of about 0.780");
    const uint32_t c2[] = {1, 1}; const uint32_t t2[] = {2, 3};
    reps_check("two tasks fail", !rmsSchedulable(c2, t2, 2), "0.833 is over the 2-task bound of about 0.828");
    const uint32_t c3[] = {1}; const uint32_t t3[] = {1};
    reps_check("one task at the bound", rmsSchedulable(c3, t3, 1), "a single task at 100% meets the 1-task bound of 1.0");
    reps_check("no tasks", rmsSchedulable(c3, t3, 0), "zero tasks are always schedulable");
    const uint32_t c4[] = {3, 2}; const uint32_t t4[] = {10, 7};
    reps_check("integer division trap", std::fabs(utilization(c4, t4, 2) - (0.3 + 2.0 / 7.0)) < 1e-9, "3/10 + 2/7 must not round down to 0");
    return 0;
}
