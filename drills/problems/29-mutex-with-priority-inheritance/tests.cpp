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
    Task low{1, 1, 1}, med{2, 2, 2}, high{3, 3, 3};
    PiMutex m;
    reps_check("starts free", m.owner() == nullptr, "a new mutex has no owner");
    reps_check("lock when free", m.lock(low) && m.owner() == &low, "low should take the free mutex");
    reps_check("med waits, low inherits 2", !m.lock(med) && low.priority == 2, "low should inherit priority 2 from the waiting med task");
    reps_check("high waits, low inherits 3", !m.lock(high) && low.priority == 3, "low should inherit priority 3 from the waiting high task");
    reps_check("non-owner unlock ignored", m.unlock(med) == nullptr && m.owner() == &low, "only the owner can unlock");
    Task* next = m.unlock(low);
    reps_check("handoff to highest waiter", next == &high && m.owner() == &high, "unlock should hand the mutex to high even though med waited first");
    reps_check("priority restored", low.priority == 1, "low's priority should return to its base of 1");
    reps_check("then next waiter", m.unlock(high) == &med && m.owner() == &med, "high's unlock should hand the mutex to med");
    reps_check("free after last unlock", m.unlock(med) == nullptr && m.owner() == nullptr, "with no waiters the mutex becomes free");
    Task a{10, 1, 1}, b{11, 3, 3}, c{12, 3, 3};
    PiMutex t;
    t.lock(a); t.lock(b); t.lock(c);
    reps_check("tie goes to earliest waiter", t.unlock(a) == &b, "b and c tie at priority 3; b waited first");
    const PiMutex& ct = t;
    reps_check("owner is const", ct.owner() == &b, "owner should work on a const mutex");
    return 0;
}
