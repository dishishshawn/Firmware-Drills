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
    ByteQueue q;
    reps_check("starts empty", q.size() == 0, "size() of a new queue should be 0");
    uint8_t b = 0;
    reps_check("pop on empty fails", q.pop(b) == false, "pop on an empty queue should return false");
    bool all = true;
    for (int i = 0; i < 16; ++i) all = all && q.push(static_cast<uint8_t>(i + 1));
    reps_check("holds 16", all, "the first 16 pushes should all return true");
    reps_check("17th push fails", q.push(99) == false, "a push into a full queue should return false");
    reps_check("size when full", q.size() == 16, "size() should be 16 when full");
    bool order = true;
    for (int i = 0; i < 16; ++i) { uint8_t v = 0; order = order && q.pop(v) && v == static_cast<uint8_t>(i + 1); }
    reps_check("first in, first out", order, "pops should return 1..16 in push order");
    reps_check("empty again", q.size() == 0 && q.pop(b) == false, "after popping everything the queue should be empty");
    bool wrap = true;
    for (int round = 0; round < 3; ++round) {
        for (int i = 0; i < 10; ++i) wrap = wrap && q.push(static_cast<uint8_t>(round * 10 + i));
        for (int i = 0; i < 10; ++i) { uint8_t v = 0; wrap = wrap && q.pop(v) && v == static_cast<uint8_t>(round * 10 + i); }
    }
    reps_check("wraps around", wrap, "repeated push/pop cycles past the end of the array should keep order");
    const ByteQueue& cq = q;
    reps_check("size is const", cq.size() == 0, "size() should be callable on a const queue");
    return 0;
}
