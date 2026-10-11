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
struct reps_Msg { uint32_t id; uint8_t len; };
int main() {
    MessageQueue<int, 4> q;
    bool sent = true;
    for (int i = 1; i <= 4; ++i) sent = sent && q.sendFromIsr(i);
    reps_check("holds N messages", sent && q.size() == 4u, "a queue of capacity 4 should accept 4 messages");
    reps_check("drops when full", !q.sendFromIsr(5) && q.dropped() == 1u, "the 5th message should be dropped and counted");
    int v = 0; bool order = true;
    for (int i = 1; i <= 4; ++i) order = order && q.receive(v) && v == i;
    reps_check("first in, first out", order, "messages should come out 1, 2, 3, 4");
    reps_check("empty receive", !q.receive(v) && q.size() == 0u, "receive on an empty queue returns false");
    bool wrap = true;
    for (int round = 0; round < 5; ++round) {
        wrap = wrap && q.sendFromIsr(round * 10) && q.sendFromIsr(round * 10 + 1);
        int a = -1, b = -1;
        wrap = wrap && q.receive(a) && q.receive(b) && a == round * 10 && b == round * 10 + 1;
    }
    reps_check("wraps around", wrap, "repeated send/receive past the end of the array keeps order");
    MessageQueue<reps_Msg, 2> frames;
    reps_Msg m{0x123, 3};
    frames.sendFromIsr(m);
    reps_Msg out{0, 0};
    reps_check("works with structs", frames.receive(out) && out.id == 0x123u && out.len == 3, "a struct message should round trip");
    const MessageQueue<int, 4>& cq = q;
    reps_check("const accessors", cq.size() == 0u && cq.dropped() == 1u, "size and dropped should work on a const queue");
    return 0;
}
