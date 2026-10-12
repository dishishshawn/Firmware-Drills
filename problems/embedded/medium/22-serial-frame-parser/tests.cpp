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
static bool reps_feedAll(FrameParser& p, const uint8_t* bytes, int n) {
    bool last = false;
    for (int i = 0; i < n; ++i) last = p.feed(bytes[i]);
    return last;
}
int main() {
    FrameParser p;
    const uint8_t f1[] = {0xAA, 0x03, 0x01, 0x02, 0x03, 0x03};
    bool early = false;
    for (int i = 0; i < 5; ++i) early = early || p.feed(f1[i]);
    bool done = p.feed(f1[5]);
    reps_check("valid frame", !early && done, "only the checksum byte should return true");
    reps_check("payload", p.length() == 3 && p.payload()[0] == 1 && p.payload()[1] == 2 && p.payload()[2] == 3, "length 3, payload 01 02 03");
    const uint8_t f2[] = {0x00, 0xFF, 0xAA, 0x01, 0x7E, 0x7F};
    reps_check("skips garbage", reps_feedAll(p, f2, 6) && p.length() == 1 && p.payload()[0] == 0x7E, "bytes before AA should be ignored");
    const uint8_t bad[] = {0xAA, 0x01, 0x05, 0x99};
    reps_check("bad checksum rejected", !reps_feedAll(p, bad, 4), "a wrong checksum should not complete a frame");
    const uint8_t f3[] = {0xAA, 0x01, 0x05, 0x04};
    reps_check("recovers after bad frame", reps_feedAll(p, f3, 4) && p.length() == 1 && p.payload()[0] == 0x05, "the next good frame should parse");
    const uint8_t empty[] = {0xAA, 0x00, 0x00};
    reps_check("zero-length frame", reps_feedAll(p, empty, 3) && p.length() == 0, "AA 00 00 is a valid empty frame");
    const uint8_t tooLong[] = {0xAA, 0x11};
    bool tl = reps_feedAll(p, tooLong, 2);
    const uint8_t f4[] = {0xAA, 0x01, 0x05, 0x04};
    reps_check("length over 16 rejected", !tl && reps_feedAll(p, f4, 4), "length 17 should be dropped and the next frame parsed");
    const uint8_t f5[] = {0xAA, 0x02, 0xAA, 0x55, 0xFD};
    reps_check("0xAA inside payload", reps_feedAll(p, f5, 5) && p.length() == 2 && p.payload()[0] == 0xAA && p.payload()[1] == 0x55, "0xAA inside a frame is data");
    const FrameParser& cp = p;
    reps_check("const accessors", cp.length() == 2 && cp.payload() != nullptr, "length and payload should work on a const parser");
    return 0;
}
