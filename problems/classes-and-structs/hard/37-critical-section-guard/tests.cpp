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
static_assert(!std::is_copy_constructible<CriticalSection>::value, "copying a CriticalSection should not compile (= delete the copy constructor)");
static_assert(!std::is_copy_assignable<CriticalSection>::value, "assigning a CriticalSection should not compile (= delete the copy assignment operator)");
int main() {
    g_irqEnabled = true;
    bool inside = true, afterInner = true;
    {
        CriticalSection a;
        inside = g_irqEnabled;
        {
            CriticalSection b;
        }
        afterInner = g_irqEnabled;
    }
    reps_check("disables", !inside, "interrupts should be off while a CriticalSection exists (is it a named object?)");
    reps_check("nested keeps off", !afterInner, "ending an inner section must not turn interrupts on inside the outer one");
    reps_check("restores on", g_irqEnabled, "interrupts should be back on after the outer section ends");

    g_irqEnabled = false;
    {
        CriticalSection c;
    }
    reps_check("restores off", !g_irqEnabled, "if interrupts were already off (inside an ISR), they stay off");

    g_irqEnabled = true;
    uint32_t used = 0;
    unsigned before = g_irqSaves;
    bool claimed = claimSlot(used, 2) && claimSlot(used, 2);
    reps_check("claims", claimed && used == 2u && g_irqEnabled, "two claims under a limit of 2 should succeed");
    reps_check("full", !claimSlot(used, 2) && used == 2u, "a third claim should fail and leave the count at 2");
    reps_check("early return restores", g_irqEnabled, "interrupts should be back on after the early return");
    reps_check("uses the guard", g_irqSaves - before == 3u, "each claimSlot call should make exactly one CriticalSection");
    return 0;
}
