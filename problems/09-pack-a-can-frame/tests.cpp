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
    CanFrame f = packMotorStatus(static_cast<uint16_t>(1500), static_cast<int8_t>(-5));
    reps_check("id and length", f.id == 0x123u && f.len == 3, "expected id 0x123 and len 3");
    reps_check("speed little-endian", f.data[0] == 0xDC && f.data[1] == 0x05, "speed 1500 should be bytes 0xDC 0x05");
    reps_check("temperature byte", f.data[2] == 0xFB, "temperature -5 should be byte 0xFB");
    uint16_t s = 0; int8_t t = 0;
    bool ok = unpackMotorStatus(f, s, t);
    reps_check("round trip", ok && s == 1500 && t == -5, "unpack should return true, 1500, -5");
    CanFrame g = packMotorStatus(static_cast<uint16_t>(65535), static_cast<int8_t>(127));
    uint16_t s2 = 0; int8_t t2 = 0;
    reps_check("max values", unpackMotorStatus(g, s2, t2) && s2 == 65535 && t2 == 127, "65535 and 127 should round trip");
    CanFrame bad = f; bad.id = 0x124;
    uint16_t s3 = 7; int8_t t3 = 7;
    reps_check("wrong id rejected", !unpackMotorStatus(bad, s3, t3) && s3 == 7 && t3 == 7, "wrong id should return false and leave outputs untouched");
    CanFrame shortF = f; shortF.len = 2;
    reps_check("wrong length rejected", !unpackMotorStatus(shortF, s3, t3) && s3 == 7 && t3 == 7, "len 2 should return false and leave outputs untouched");
    return 0;
}
