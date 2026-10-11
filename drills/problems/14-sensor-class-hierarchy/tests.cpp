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
#include <memory>
#include <type_traits>
#include <vector>
static_assert(std::is_abstract<Sensor>::value, "Sensor must be abstract (have a pure virtual function)");
static_assert(std::has_virtual_destructor<Sensor>::value, "Sensor needs a virtual destructor");
int main() {
    TemperatureSensor t(750);
    reps_check("temperature conversion", std::fabs(t.read() - 25.0) < 1e-9, "count 750 should read 25.0");
    PressureSensor p(101.3);
    reps_check("pressure passthrough", std::fabs(p.read() - 101.3) < 1e-9, "101.3 kPa should read 101.3");
    const Sensor& base = t;
    reps_check("virtual dispatch", std::fabs(base.read() - 25.0) < 1e-9, "read through a const Sensor reference should call the derived class");
    std::vector<std::unique_ptr<Sensor>> v;
    reps_check("empty average", averageReading(v) == 0.0, "an empty vector should average 0.0");
    v.push_back(std::make_unique<TemperatureSensor>(750));
    v.push_back(std::make_unique<PressureSensor>(101.3));
    reps_check("mixed average", std::fabs(averageReading(v) - 63.15) < 1e-9, "25.0 and 101.3 should average 63.15");
    return 0;
}
