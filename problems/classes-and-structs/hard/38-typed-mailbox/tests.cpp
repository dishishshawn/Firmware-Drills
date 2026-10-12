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
struct SensorMsg {
    uint8_t id;
    int16_t value;
};
static_assert(sizeof(Mailbox<uint32_t, 8>) >= 8 * sizeof(uint32_t), "the messages should be stored inside the object, not on the heap");
int main() {
    Mailbox<SensorMsg, 2> mb;
    reps_check("starts empty", mb.empty() && !mb.full() && mb.size() == 0u && mb.peek() == nullptr, "a new mailbox is empty and peek returns nullptr");
    bool s1 = mb.send({1, 20}), s2 = mb.send({2, 30}), s3 = mb.send({3, 40});
    reps_check("send until full", s1 && s2 && !s3 && mb.full() && mb.size() == 2u, "capacity 2: send, send, then false");
    const Mailbox<SensorMsg, 2>& view = mb;
    reps_check("peek oldest", view.peek() != nullptr && view.peek()->id == 1 && view.size() == 2u, "peek shows the oldest message without removing it");
    SensorMsg m{};
    reps_check("receive oldest", mb.receive(m) && m.id == 1 && m.value == 20 && mb.size() == 1u, "receive copies out the oldest message and removes it");
    reps_check("send after receive", mb.send({4, -5}), "receiving frees a slot");
    bool r2 = mb.receive(m) && m.id == 2;
    bool r3 = mb.receive(m) && m.id == 4 && m.value == -5;
    reps_check("first in, first out", r2 && r3, "messages come out in the order they went in");
    m.id = 99;
    reps_check("receive when empty", !mb.receive(m) && m.id == 99 && mb.empty(), "receive on an empty mailbox returns false and leaves the argument alone");

    Mailbox<int, 3> q;
    bool order = true;
    int next = 0, expect = 0;
    for (int round = 0; round < 50; ++round) {
        while (q.send(next)) ++next;
        int v = -1;
        for (int k = 0; k < 2; ++k) order = order && q.receive(v) && v == expect++;
    }
    reps_check("ring wraps", order && q.size() == 1u, "after 50 rounds of fill-and-drain-2, every message should come out in order");

    Mailbox<int, 1> one;
    int got = 0;
    reps_check("capacity 1", one.send(7) && !one.send(8) && one.full() && one.receive(got) && got == 7 && one.empty(), "a mailbox of 1 holds one message");
    return 0;
}
