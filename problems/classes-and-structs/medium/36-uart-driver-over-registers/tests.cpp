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
static_assert(sizeof(UartRegs) == 16, "UartRegs should be exactly four 32-bit registers");
static_assert(offsetof(UartRegs, DR) == 4 && offsetof(UartRegs, BRR) == 8 && offsetof(UartRegs, CR1) == 12, "registers must be in the order SR, DR, BRR, CR1");
static_assert(std::is_volatile<decltype(UartRegs::SR)>::value && std::is_volatile<decltype(UartRegs::CR1)>::value, "hardware registers must be volatile");
int main() {
    UartRegs regs{};
    Uart uart(regs);
    uart.init(16000000u, 115200u);
    reps_check("baud rate rounds up", regs.BRR == 139u, "16000000 / 115200 = 138.89, which rounds to 139 (and keep a reference to the registers, not a copy)");
    reps_check("enables", regs.CR1 == 0x200Cu, "CR1 should be UE | TE | RE = 0x200C");
    uart.init(8000000u, 9600u);
    reps_check("baud rate rounds down", regs.BRR == 833u, "8000000 / 9600 = 833.33, which rounds to 833");
    regs.SR = 0;
    reps_check("write waits for TXE", !uart.write(0x41) && regs.DR == 0u, "with TXE clear, write returns false and leaves DR alone");
    regs.SR = 1u << 7;
    reps_check("write when ready", uart.write(0x41) && regs.DR == 0x41u, "with TXE set, write puts the byte in DR");
    uint8_t got = 0;
    reps_check("read waits for RXNE", !uart.read(got) && got == 0, "with RXNE clear, read returns false");
    regs.SR = 1u << 5;
    regs.DR = 0x1234u;
    reps_check("read when ready", uart.read(got) && got == 0x34, "with RXNE set, read returns the low 8 bits of DR");
    regs.SR = ~(1u << 7);
    reps_check("write tests only TXE", !uart.write(0x42) && regs.DR == 0x1234u, "every SR bit but TXE is set: write must check bit 7 itself");
    return 0;
}
