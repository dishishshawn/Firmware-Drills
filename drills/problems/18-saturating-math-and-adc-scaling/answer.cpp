// 18  Saturating math and ADC scaling  [EASY] [EMBEDDED]
// Embedded, target 12 min. Unit tests call the names below.
//
// Control loops clamp instead of wrapping, and most MCUs have no floating-point budget
// to spare. Write a saturating add and an integer-only ADC conversion.
//
// What to write:
//   - A function named satAdd16 that takes two signed 16-bit values and returns their
//     sum as a signed 16-bit value, clamped to the range -32768 to 32767 instead of
//     wrapping.
//   - A function named adcToMillivolts that takes a 12-bit ADC count as an unsigned
//     16-bit value and returns millivolts as an unsigned 32-bit value, for a 3300 mV
//     reference: count times 3300 divided by 4095, rounded to the nearest millivolt.
//     Counts above 4095 are treated as 4095.
//
// Examples:
//   satAdd16(32000, 1000) -> 32767
//   satAdd16(-32000, -1000) -> -32768
//   adcToMillivolts(4095) -> 3300
//   adcToMillivolts(2048) -> 1650
//
// Constraints:
//   - Integer math only. No floating point.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

#include <stdint.h>

int16_t satAdd16(int16_t first, int16_t second) {
    int32_t sum = 0;
    sum = (int32_t)first + (int32_t)second;
    if (sum > INT16_MAX) {
        return INT16_MAX;
    }
    if (sum < INT16_MIN) {
        return INT16_MIN;
    }
    return (int16_t)sum;
}

uint32_t adcToMillivolts(uint16_t ADC_count) {
    uint32_t mV = ((uint32_t)ADC_count * 3300 + 4095 / 2) / 4095;
    if(ADC_count > 4095) {
        return mV = 3300;
    }
    return mV;
}
