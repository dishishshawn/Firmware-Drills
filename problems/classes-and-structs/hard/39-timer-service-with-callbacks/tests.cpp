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
static int g_log[16];
static size_t g_logLen = 0;
static void record(void* ctx) {
    if (g_logLen < 16) g_log[g_logLen++] = *static_cast<int*>(ctx);
}
struct Counter {
    int fires = 0;
};
static void bump(void* ctx) { ++static_cast<Counter*>(ctx)->fires; }
struct SelfCancel {
    TimerService* svc;
    int handle;
    int fires;
};
static void cancelSelf(void* ctx) {
    SelfCancel* s = static_cast<SelfCancel*>(ctx);
    ++s->fires;
    s->svc->cancel(s->handle);
}
int main() {
    TimerService svc;
    Counter c;
    int h = svc.create(2, false, bump, &c);
    size_t t1 = svc.tick(), t2 = svc.tick(), t3 = svc.tick();
    reps_check("one-shot fires once", h == 0 && t1 == 0u && t2 == 1u && t3 == 0u && c.fires == 1, "create(2, false, ...) -> handle 0; ticks return 0, 1, 0");
    reps_check("one-shot frees its slot", svc.active() == 0u, "a one-shot timer frees its slot when it fires");

    TimerService p;
    Counter pc;
    int ph = p.create(3, true, bump, &pc);
    for (int i = 0; i < 9; ++i) p.tick();
    reps_check("periodic reloads", pc.fires == 3 && p.active() == 1u, "period 3 over 9 ticks fires 3 times and stays in use");
    reps_check("cancel", p.cancel(ph) && p.active() == 0u, "cancel frees the slot and returns true");
    for (int i = 0; i < 6; ++i) p.tick();
    reps_check("cancelled stays quiet", pc.fires == 3, "a cancelled timer never fires");
    reps_check("bad handles", !p.cancel(ph) && !p.cancel(-1) && !p.cancel(8) && !p.cancel(1000), "cancel returns false for an unused or out-of-range handle");

    TimerService full;
    Counter fc;
    bool all = true;
    for (int i = 0; i < 8; ++i) all = all && full.create(10, true, bump, &fc) == i;
    reps_check("eight slots", all && full.create(1, false, bump, &fc) == -1 && full.active() == 8u, "handles 0 to 7, then -1 when full");
    full.cancel(5);
    reps_check("reuses freed slot", full.create(1, false, bump, &fc) == 5, "create should take the lowest free slot");

    TimerService order;
    int ids[3] = {10, 11, 12};
    order.create(2, false, record, &ids[0]);
    order.create(1, true, record, &ids[1]);
    order.create(2, true, record, &ids[2]);
    g_logLen = 0;
    size_t n1 = order.tick(), n2 = order.tick();
    bool seq = g_logLen == 4 && g_log[0] == 11 && g_log[1] == 10 && g_log[2] == 11 && g_log[3] == 12;
    reps_check("handle order and context", n1 == 1u && n2 == 3u && seq, "tick 1 fires handle 1; tick 2 fires handles 0, 1, 2 in order, each with its own context");

    TimerService sc;
    SelfCancel s{&sc, -1, 0};
    s.handle = sc.create(1, true, cancelSelf, &s);
    sc.tick();
    sc.tick();
    sc.tick();
    reps_check("callback cancels itself", s.fires == 1 && sc.active() == 0u, "a periodic timer that cancels itself in its callback must not fire again");
    return 0;
}
