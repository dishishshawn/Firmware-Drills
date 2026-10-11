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
    Debouncer d(3);
    bool a = d.update(true), b = d.update(true), c = d.update(true);
    reps_check("press after 3 samples", !a && !b && c, "true, true, true should give false, false, true");
    reps_check("press event once", d.pressedEvent() && !d.pressedEvent(), "pressedEvent should be true once, then false");
    bool r1 = d.update(false), r2 = d.update(false), r3 = d.update(false);
    reps_check("release after 3 samples", r1 && r2 && !r3, "false, false, false should give true, true, false");
    reps_check("no event on release", !d.pressedEvent(), "releasing the button is not a press event");
    Debouncer bounce(3);
    const bool raw[] = {true, false, true, true, false, true, true, true};
    bool outs[8];
    for (int i = 0; i < 8; ++i) outs[i] = bounce.update(raw[i]);
    bool ok = true;
    for (int i = 0; i < 7; ++i) ok = ok && !outs[i];
    reps_check("bounce resets the count", ok && outs[7], "only three steady trues in a row should change the state");
    Debouncer fast(1);
    reps_check("one-sample debouncer", fast.update(true) && fast.pressedEvent(), "with 1 sample required, the first true should press");
    Debouncer again(2);
    again.update(true); again.update(true); again.pressedEvent();
    again.update(false); again.update(false);
    again.update(true); again.update(true);
    reps_check("second press gives a new event", again.pressedEvent(), "pressing again after a release should raise a new event");
    return 0;
}
