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
    reps_check("empty list", reverseList(nullptr) == nullptr, "reversing a null list should return a null pointer");
    Node one; one.value = 7; one.next = nullptr;
    Node* r1 = reverseList(&one);
    reps_check("single node", r1 == &one && r1->next == nullptr, "a one-node list should come back unchanged");
    Node a, b, c; a.value = 1; b.value = 2; c.value = 3; a.next = &b; b.next = &c; c.next = nullptr;
    Node* r = reverseList(&a);
    bool ok = r == &c && c.next == &b && b.next == &a && a.next == nullptr;
    reps_check("three nodes", ok, "1 -> 2 -> 3 should become 3 -> 2 -> 1 using the same nodes");
    Node n[5];
    for (int i = 0; i < 5; ++i) { n[i].value = i; n[i].next = (i < 4) ? &n[i + 1] : nullptr; }
    Node* p = reverseList(&n[0]);
    bool ok5 = true; int expect = 4; int count = 0;
    while (p != nullptr && count < 10) { ok5 = ok5 && p->value == expect; --expect; p = p->next; ++count; }
    reps_check("five nodes", ok5 && count == 5, "0..4 should read 4..0 after reversing");
    return 0;
}
