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
static_assert(std::is_same<decltype(Reading::raw), uint16_t>::value, "raw should be a uint16_t");
static_assert(std::is_same<decltype(Reading::tick), uint32_t>::value, "tick should be a uint32_t");
int main() {
    const Reading r{1, 750, 100};
    reps_check("celsius", std::fabs(r.celsius() - 25.0) < 1e-9, "raw 750 should be 25.0 C");
    reps_check("celsius at zero", std::fabs(Reading{2, 0, 0}.celsius() + 50.0) < 1e-9, "raw 0 should be -50.0 C");
    Reading readings[] = {{1, 750, 100}, {2, 900, 101}, {3, 600, 102}};
    reps_check("hottest", hottest(readings, 3) == &readings[1], "the hottest of 750, 900, 600 is readings[1]; return a pointer into the array, not to a copy");
    reps_check("empty", hottest(readings, 0) == nullptr, "length 0 should return nullptr");
    reps_check("one reading", hottest(readings + 2, 1) == &readings[2], "a single reading is the hottest");
    Reading rising[] = {{4, 100, 1}, {5, 200, 2}, {6, 300, 3}};
    reps_check("hottest is last", hottest(rising, 3) == &rising[2], "check the last element too");
    Reading tie[] = {{7, 800, 1}, {8, 800, 2}, {9, 100, 3}};
    reps_check("tie keeps first", hottest(tie, 3) == &tie[0], "on a tie, return the first");
    return 0;
}
