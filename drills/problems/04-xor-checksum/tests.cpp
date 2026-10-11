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
    const uint8_t a[] = {0x12, 0x34};
    reps_check("two bytes", xorChecksum(a, 2) == 0x26, "0x12 ^ 0x34 should be 0x26");
    reps_check("zero length", xorChecksum(a, 0) == 0, "XOR of no bytes should be 0");
    const uint8_t good[] = {0x12, 0x34, 0x26};
    const uint8_t badp[] = {0x12, 0x34, 0x27};
    reps_check("valid packet", isValidPacket(good, 3), "0x12 0x34 0x26 should be valid");
    reps_check("invalid packet", !isValidPacket(badp, 3), "0x12 0x34 0x27 should be invalid");
    const uint8_t one[] = {0x00};
    reps_check("too short", !isValidPacket(one, 1) && !isValidPacket(one, 0), "packets shorter than 2 bytes are invalid");
    const uint8_t pair[] = {0xAB, 0xAB};
    reps_check("two-byte packet", isValidPacket(pair, 2), "0xAB 0xAB should be valid");
    return 0;
}
