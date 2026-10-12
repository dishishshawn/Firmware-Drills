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
#include <type_traits>
static_assert(std::is_same<decltype(Led::pin), uint8_t>::value, "Led::pin should be a uint8_t");
static_assert(std::is_same<decltype(Led::on), bool>::value, "Led::on should be a bool");
int main() {
    Led status{13};
    reps_check("brace init", status.pin == 13 && !status.on, "Led status{13} should have pin 13 and start off");
    turnOn(status);
    reps_check("turnOn", status.on, "turnOn should light the LED (take the Led by reference, Led&, or you change a copy)");
    turnOn(status);
    reps_check("turnOn when lit", status.on, "turning on a lit LED keeps it on");
    toggle(status);
    reps_check("toggle off", !status.on, "toggle should turn a lit LED off");
    toggle(status);
    reps_check("toggle on", status.on, "toggle should turn it back on");
    Led power{2};
    reps_check("separate LEDs", power.pin == 2 && !power.on && status.on, "each Led keeps its own pin and state");
    const Led& lit = status;
    reps_check("isLit", isLit(lit) && !isLit(power), "isLit should return on, through a read-only reference");
    return 0;
}
