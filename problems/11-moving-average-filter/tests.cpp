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
    MovingAverage m;
    reps_check("no samples", m.average() == 0.0, "average with no samples should be 0.0");
    m.add(10); m.add(20);
    reps_check("partial window", std::fabs(m.average() - 15.0) < 1e-9, "10 and 20 should average 15.0");
    MovingAverage w;
    for (int i = 0; i < 8; ++i) w.add(100);
    w.add(0);
    reps_check("oldest replaced", std::fabs(w.average() - 87.5) < 1e-9, "8 x 100 then 0 should average 87.5");
    MovingAverage hi;
    for (int i = 0; i < 20; ++i) hi.add(32767);
    reps_check("no overflow high", std::fabs(hi.average() - 32767.0) < 1e-9, "all 32767 should average 32767");
    MovingAverage lo;
    for (int i = 0; i < 20; ++i) lo.add(-32768);
    reps_check("no overflow low", std::fabs(lo.average() + 32768.0) < 1e-9, "all -32768 should average -32768");
    const MovingAverage& c = w;
    reps_check("average is const", std::fabs(c.average() - 87.5) < 1e-9, "average() should be callable on a const object");
    return 0;
}
