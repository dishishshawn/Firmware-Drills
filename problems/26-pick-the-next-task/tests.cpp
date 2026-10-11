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
    const Task a[] = {{1, TaskState::Ready}, {3, TaskState::Blocked}, {2, TaskState::Ready}};
    reps_check("highest ready wins", pickNext(a, 3, -1) == 2, "the blocked priority-3 task must be skipped");
    const Task none[] = {{1, TaskState::Blocked}, {2, TaskState::Suspended}};
    reps_check("nothing ready", pickNext(none, 2, -1) == -1, "no ready task should return -1");
    const Task rr[] = {{2, TaskState::Ready}, {2, TaskState::Ready}, {2, TaskState::Ready}};
    reps_check("first run", pickNext(rr, 3, -1) == 0, "with nothing run yet, start at index 0");
    reps_check("round robin", pickNext(rr, 3, 0) == 1, "after index 0 ran, index 1 is next");
    reps_check("round robin wraps", pickNext(rr, 3, 2) == 0, "after the last index ran, wrap to 0");
    const Task mix[] = {{2, TaskState::Ready}, {5, TaskState::Ready}, {5, TaskState::Suspended}, {5, TaskState::Ready}};
    reps_check("skip non-ready peer", pickNext(mix, 4, 1) == 3, "the suspended priority-5 task is skipped");
    reps_check("peer wraps back", pickNext(mix, 4, 3) == 1, "after index 3 ran, wrap back to index 1");
    const Task low[] = {{1, TaskState::Ready}, {4, TaskState::Ready}, {4, TaskState::Ready}};
    reps_check("lastRun was lower priority", pickNext(low, 3, 0) == 1, "after a low-priority task ran, take the first top-priority task after it");
    reps_check("empty array", pickNext(low, 0, -1) == -1, "zero tasks should return -1");
    return 0;
}
