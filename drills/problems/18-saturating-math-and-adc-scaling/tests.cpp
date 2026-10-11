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
    reps_check("normal add", satAdd16(100, 200) == 300, "100 + 200 should be 300");
    reps_check("clamp high", satAdd16(32000, 1000) == 32767, "32000 + 1000 should clamp to 32767");
    reps_check("clamp low", satAdd16(-32000, -1000) == -32768, "-32000 + -1000 should clamp to -32768");
    reps_check("near the edge", satAdd16(32767, -1) == 32766, "32767 + -1 should be 32766");
    reps_check("opposite extremes", satAdd16(-32768, 32767) == -1, "-32768 + 32767 should be -1");
    reps_check("zero counts", adcToMillivolts(0) == 0u, "0 counts should be 0 mV");
    reps_check("full scale", adcToMillivolts(4095) == 3300u, "4095 counts should be 3300 mV");
    reps_check("mid scale", adcToMillivolts(2048) == 1650u, "2048 counts should round to 1650 mV");
    reps_check("rounds up", adcToMillivolts(1) == 1u, "1 count is 0.806 mV, which rounds to 1");
    reps_check("over range", adcToMillivolts(5000) == 3300u, "counts above 4095 should read as 3300 mV");
    return 0;
}
