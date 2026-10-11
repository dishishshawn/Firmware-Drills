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
    SoftTimer t;
    reps_check("starts stopped", !t.isRunning() && !t.tick(), "a new timer is stopped and never fires");
    t.start(3u, false);
    bool a = t.tick(), b = t.tick(), c = t.tick(), d = t.tick(), e = t.tick();
    reps_check("one-shot fires once", !a && !b && c && !d && !e, "start(3, false) should fire on the 3rd tick only");
    reps_check("one-shot stops", !t.isRunning(), "a one-shot timer stops after firing");
    SoftTimer p;
    p.start(2u, true);
    bool seq[6]; for (int i = 0; i < 6; ++i) seq[i] = p.tick();
    reps_check("periodic", !seq[0] && seq[1] && !seq[2] && seq[3] && !seq[4] && seq[5], "start(2, true) should fire every 2nd tick");
    reps_check("periodic keeps running", p.isRunning(), "a periodic timer keeps running");
    SoftTimer s;
    s.start(2u, true); s.tick(); s.stop();
    bool any = false; for (int i = 0; i < 3; ++i) any = any || s.tick();
    reps_check("stop disarms", !any && !s.isRunning(), "a stopped timer never fires");
    SoftTimer r;
    r.start(3u, false); r.tick(); r.tick(); r.start(3u, false);
    bool r1 = r.tick(), r2 = r.tick(), r3 = r.tick();
    reps_check("restart resets the count", !r1 && !r2 && r3, "restarting should count the full period again");
    const SoftTimer& ct = p;
    reps_check("isRunning is const", ct.isRunning(), "isRunning should work on a const timer");
    return 0;
}
