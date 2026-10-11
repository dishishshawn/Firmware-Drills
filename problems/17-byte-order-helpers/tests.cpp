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
    reps_check("swap16", swap16(0x1234u) == 0x3412u, "swap16(0x1234) should be 0x3412");
    reps_check("swap32", swap32(0x12345678u) == 0x78563412u, "swap32(0x12345678) should be 0x78563412");
    reps_check("swap32 twice", swap32(swap32(0xCAFEF00Du)) == 0xCAFEF00Du, "swapping twice should give back the original");
    const uint8_t be[4] = {0xDE, 0xAD, 0xBE, 0xEF};
    reps_check("read big-endian", readBigEndian32(be) == 0xDEADBEEFu, "DE AD BE EF should read as 0xDEADBEEF");
    const uint8_t hi[4] = {0x80, 0x00, 0x00, 0x01};
    reps_check("read with top bit set", readBigEndian32(hi) == 0x80000001u, "80 00 00 01 should read as 0x80000001");
    uint8_t out[4] = {0, 0, 0, 0};
    writeLittleEndian32(out, 0x11223344u);
    reps_check("write little-endian", out[0] == 0x44 && out[1] == 0x33 && out[2] == 0x22 && out[3] == 0x11, "0x11223344 should be written as 44 33 22 11");
    return 0;
}
