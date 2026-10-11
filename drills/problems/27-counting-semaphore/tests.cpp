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
    CountingSemaphore s(2u, 2u);
    reps_check("takes available", s.tryTake(1) && s.tryTake(2) && s.count() == 0u, "two takes from a count of 2 should succeed");
    reps_check("blocks when empty", !s.tryTake(3) && !s.tryTake(4) && s.waiting() == 2u, "takes at count 0 should fail and queue the task");
    reps_check("give wakes first waiter", s.give() == 3 && s.waiting() == 1u && s.count() == 0u, "give should hand the resource to task 3 first");
    reps_check("give wakes next waiter", s.give() == 4 && s.waiting() == 0u, "then to task 4");
    reps_check("give with no waiters", s.give() == -1 && s.count() == 1u, "with nobody waiting, give raises the count");
    s.give();
    reps_check("count capped at maximum", s.give() == -1 && s.count() == 2u, "the count must not pass the maximum of 2");
    CountingSemaphore b(0u, 1u);
    reps_check("binary semaphore signalling", !b.tryTake(5) && b.give() == 5 && b.give() == -1 && b.count() == 1u, "a waiting task should be released by give");
    CountingSemaphore full(0u, 1u);
    for (int i = 0; i < 9; ++i) full.tryTake(100 + i);
    reps_check("wait list capped at 8", full.waiting() == 8u, "the 9th waiter should not be added");
    bool order = true;
    for (int i = 0; i < 8; ++i) order = order && full.give() == 100 + i;
    reps_check("first in, first out", order, "waiters should be released in the order they arrived");
    const CountingSemaphore& c = s;
    reps_check("const accessors", c.count() == 2u && c.waiting() == 0u, "count and waiting should work on a const semaphore");
    return 0;
}
