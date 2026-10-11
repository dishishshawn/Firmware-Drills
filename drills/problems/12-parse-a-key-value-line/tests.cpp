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
#include <string>
int main() {
    std::string k; int v = 0;
    reps_check("positive value", parseKeyValue("speed=1500", k, v) && k == "speed" && v == 1500, "speed=1500 should give speed, 1500");
    reps_check("negative value", parseKeyValue("temp=-5", k, v) && k == "temp" && v == -5, "temp=-5 should give temp, -5");
    reps_check("zero", parseKeyValue("k=0", k, v) && k == "k" && v == 0, "k=0 should give k, 0");
    reps_check("empty key", !parseKeyValue("=4", k, v), "=4 should be rejected");
    reps_check("not a number", !parseKeyValue("mode=fast", k, v), "mode=fast should be rejected");
    reps_check("no equals sign", !parseKeyValue("speed1500", k, v), "a line without = should be rejected");
    reps_check("empty value", !parseKeyValue("x=", k, v), "x= should be rejected");
    reps_check("lone minus", !parseKeyValue("x=-", k, v), "x=- should be rejected");
    reps_check("trailing junk", !parseKeyValue("x=12a", k, v), "x=12a should be rejected");
    return 0;
}
