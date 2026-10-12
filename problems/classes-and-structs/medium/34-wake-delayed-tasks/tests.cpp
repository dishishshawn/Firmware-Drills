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
    Tcb t{1, 5};
    reps_check("new task is ready", t.id == 1 && t.priority == 5 && t.state == TaskState::Ready && t.wakeTick == 0u, "Tcb t{1, 5} should be Ready with wakeTick 0");
    delayTask(t, 100, 10);
    reps_check("delay blocks", t.state == TaskState::Blocked && t.wakeTick == 110u, "delayTask(t, 100, 10) should block the task until tick 110");
    reps_check("not yet", wakeDue(&t, 1, 109) == 0u && t.state == TaskState::Blocked, "at tick 109 the task is still blocked");
    reps_check("wakes on time", wakeDue(&t, 1, 110) == 1u && t.state == TaskState::Ready, "at tick 110 the task should wake");
    reps_check("ready not counted", wakeDue(&t, 1, 200) == 0u, "a Ready task is not woken again");
    Tcb tasks[] = {{1, 3}, {2, 2}, {3, 1}, {4, 4}};
    delayTask(tasks[0], 0, 5);
    delayTask(tasks[1], 0, 20);
    delayTask(tasks[2], 0, 5);
    tasks[2].state = TaskState::Suspended;
    reps_check("wakes only due tasks", wakeDue(tasks, 4, 10) == 1u && tasks[0].state == TaskState::Ready && tasks[1].state == TaskState::Blocked, "at tick 10 only task 1 is due");
    reps_check("suspended stays", tasks[2].state == TaskState::Suspended, "a Suspended task is not woken, even past its wakeTick");
    reps_check("late tick still wakes", wakeDue(tasks, 4, 25) == 1u && tasks[1].state == TaskState::Ready, "a task whose wakeTick has passed should wake");
    Tcb w{9, 1};
    delayTask(w, 0xFFFFFFF0u, 0x20u);
    reps_check("wake tick wraps", w.wakeTick == 0x10u, "0xFFFFFFF0 + 0x20 wraps to 0x10");
    reps_check("no early wake across wrap", wakeDue(&w, 1, 0xFFFFFFF5u) == 0u && w.state == TaskState::Blocked, "at 0xFFFFFFF5 the task still has 0x1B ticks to wait; compare with a signed difference, as in drill 19");
    reps_check("wakes after wrap", wakeDue(&w, 1, 0x10u) == 1u && w.state == TaskState::Ready, "at tick 0x10 it should wake");
    return 0;
}
