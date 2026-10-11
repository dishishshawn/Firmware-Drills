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
    const uint8_t check[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    reps_check("standard check value", crc8(check, 9) == 0xF4, "CRC-8 of 123456789 should be 0xF4");
    const uint8_t one[] = {0x01};
    reps_check("single byte", crc8(one, 1) == 0x07, "CRC-8 of 0x01 should be 0x07");
    const uint8_t ff[] = {0xFF};
    reps_check("all ones byte", crc8(ff, 1) == 0xF3, "CRC-8 of 0xFF should be 0xF3");
    reps_check("empty input", crc8(check, 0) == 0x00, "CRC-8 of nothing should be 0x00");
    const uint8_t two[] = {0x12, 0x34};
    reps_check("two bytes", crc8(two, 2) == 0xF1, "CRC-8 of 12 34 should be 0xF1");
    const uint8_t withCrc[] = {0x12, 0x34, 0xF1};
    reps_check("message plus its CRC", crc8(withCrc, 3) == 0x00, "a message followed by its CRC should check to 0");
    return 0;
}
