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
#include <vector>
static bool reps_eq(const std::vector<std::string>& got, const std::vector<std::string>& want) { return got == want; }
int main() {
    reps_check("basic sentence", reps_eq(distinctWords("the cat and the hat"), {"the", "cat", "and", "hat"}), "expected: the, cat, and, hat");
    reps_check("extra spaces and case", reps_eq(distinctWords("  a  a A "), {"a", "A"}), "expected: a, A");
    reps_check("empty string", distinctWords("").empty(), "expected an empty vector");
    reps_check("only spaces", distinctWords("     ").empty(), "expected an empty vector");
    reps_check("one word", reps_eq(distinctWords("can"), {"can"}), "expected: can");
    return 0;
}
