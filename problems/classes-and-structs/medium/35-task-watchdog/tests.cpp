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
    TaskWatchdog a;
    reps_check("first slot", a.add(3) == 0, "the first task gets slot 0");
    int r1 = a.tick(), r2 = a.tick(), r3 = a.tick();
    reps_check("expires after timeout", r1 == -1 && r2 == -1 && r3 == 0, "add(3), then 3 ticks -> -1, -1, 0");
    reps_check("stays expired", a.tick() == 0, "an expired task keeps reporting until it checks in");
    a.checkIn(0);
    reps_check("check-in clears", a.tick() == -1, "after checkIn the task has its full timeout again");

    TaskWatchdog b;
    b.add(3);
    b.tick();
    b.tick();
    b.checkIn(0);
    int s1 = b.tick(), s2 = b.tick();
    reps_check("check-in in time", s1 == -1 && s2 == -1, "checking in before the timeout keeps the task alive");

    TaskWatchdog c;
    int x = c.add(5), y = c.add(2);
    int t1 = c.tick(), t2 = c.tick();
    reps_check("per-task timeouts", x == 0 && y == 1 && t1 == -1 && t2 == 1, "add(5), add(2), 2 ticks -> slot 1 expires first");
    c.tick();
    c.tick();
    reps_check("lowest slot first", c.tick() == 0, "when slots 0 and 1 have both expired, report 0");

    TaskWatchdog d;
    bool slots = d.add(1) == 0 && d.add(1) == 1 && d.add(1) == 2 && d.add(1) == 3;
    reps_check("four slots", slots && d.add(1) == -1, "slots 0 to 3, then -1 when full");

    TaskWatchdog e;
    e.add(2);
    e.checkIn(-1);
    e.checkIn(1);
    e.checkIn(4);
    e.checkIn(1000);
    int e1 = e.tick(), e2 = e.tick();
    reps_check("unused slots ignored", e1 == -1 && e2 == 0, "checkIn on a bad slot does nothing, and slots never added never expire");
    return 0;
}
