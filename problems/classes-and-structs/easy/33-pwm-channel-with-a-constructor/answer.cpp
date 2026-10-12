// 33  PWM channel with a constructor  [EASY] [CLASS]
// Classes, embedded, target 15 min. Unit tests call the names below.
//
// A timer peripheral makes PWM by counting from 0 up to a period and switching the pin when
// the count passes a compare value: 25% duty on a period of 1000 means compare = 250. The
// class keeps duty in range so the compare register never gets a bad value. That is why
// duty is private and only setDuty can change it.
//
// What to write:
//   - A class named PwmChannel whose constructor takes the timer period in counts
//     (uint32_t). A new channel has 0% duty.
//   - A member function named setDuty that takes a percent (int). Values below 0 become 0
//     and values above 100 become 100.
//   - Member functions named duty (returns int, the stored percent) and compare (returns
//     uint32_t: period * duty / 100, rounded down). Neither modifies the channel.
//
// Examples:
//   PwmChannel ch(1000);  -> ch.compare() is 0
//   ch.setDuty(25)        -> duty() 25, compare() 250
//   ch.setDuty(150)       -> duty() 100, compare() 1000
//   ch.setDuty(-5)        -> duty() 0
//   PwmChannel(999) at 50% -> compare() 499
//
// Constraints:
//   - Set the period in the constructor's member initializer list (the ": member(value)"
//     part between the parameter list and the body).
//   - No overflow: PwmChannel(4000000000) at 100% -> compare() 4000000000.
//
// Run the "drill: run tests" task with this file open (alt-shift-t picks a task, alt-t reruns it).
// --------------------------------------------------------------------------------------

#include <cstdint>

class PwmChannel {
    public:
        // Constructor (Same name as class, runs whenever class object is created)
        PwmChannel(uint32_t counts) {
            // Default to 0% duty
            // High for counts * duty
            // Low for rest
            // compare = the count whenever switch to low
            period = counts;
            percent = 0;
        }

        void setDuty(int passedPercent) {
            if (passedPercent > 100) {
                percent = 100;
                return;
            }
            if (passedPercent < 0) {
                percent = 0;
                return;
            }
            else {
                percent = passedPercent;
            }
        }

        int duty() const{
            return percent;
        }

        uint32_t compare() const { return (uint32_t)((uint64_t)period * duty() / 100); };

    private:
        uint32_t period;
        int percent;
};
