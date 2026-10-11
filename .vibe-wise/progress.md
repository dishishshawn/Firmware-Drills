# Learning Progress

## Drill 23 (implemented by Claude at learner's request)

- Decision: Drill 23 function behavior (what tick, start, stop do to the stored state)
- Stage: Build checkpoint, learner writing code (awaiting their answer.cpp and test output)
- Asked: tick() step by step in plain English, reading/updating the note; fill in the ? cells (count on fire, start on a partway count, one-shot after firing)
- Learner's answer: (a) on each tick() call, update a counter and act on it, which is the right direction but not yet concrete and the ? cells were unanswered; (b) alternatively, a for loop inside tick, which is a misconception
- Claude explained: the caller drives the loop (tests.cpp:20, or the tick interrupt). tick() does O(1) work and returns. A loop inside it would either count everything in one call or never return.
- Learner's next answer: the counter increments on every tick() call (1, 2, 3, ...) and tick returns true when count % period == 0. This is correct for the examples (traced start(2, true)). It drops the in-tick loop idea.
- Claude flagged: a uint32_t count that keeps growing wraps after 2^32 ticks (~49.7 days at 1 ms). With period 3 it fires two ticks in a row at the wrap (4294967295 % 3 == 0, then 0 % 3 == 0).
- Now asked: (1) does the wrap matter, and how would they change the design to avoid it (tied to "what happens to the count on fire"); (2) what start does to a partway count; (3) what a one-shot changes on the note after firing. Still open: where "running?" is checked.
- Learner's answers: (1) reset the count "after every count", meaning on each fire, which avoids the wrap. Claude clarified that it resets on fire, not on every tick, and asked whether % is still needed. (2) start on a running timer would be "a separate instance, out of scope", a misreading of the spec. Claude pointed to answer.cpp:10-11 and tests.cpp:27-30: the same object restarts its count. (3) After a one-shot fires: reset the count and wait for another start (running off). Correct.
- Now asked: start() and tick() as numbered steps over period/repeats/count/running, including where tick checks running
- Learner asked "How do I write this in a class?" before writing the steps. Claude taught C++ class syntax with an unrelated DoorLock example (compiled and run with the drill flags): public/private, member variables with default initializers, member functions with parameters, a const member function, #include <cstdint> in answer.cpp, the trailing semicolon.
- Now asked: write the SoftTimer skeleton in answer.cpp (4 private members with starting values, the 4 public functions from the spec), with start/tick steps as comments first, then code. Run the tests and bring back the output for review.
- Learner wrote step comments in answer.cpp (no class yet): tick -> counter++; counter % count -> true; reset counter to zero on the tick it fires; "repeat if true". Then asked "How would you write bool tick()?"
- Claude held to the learner-writes-code preference: gave feedback on the steps (correct core logic; missing the running check, which affects tests.cpp:13 and 24-26; missing the "didn't fire" return), a C++ syntax table (++, assignment, if, ==/%, !, return, early return), and noted the class isn't declared yet. Offered to show a full version for the learner to rewrite from memory if they choose.
- Now asked: add the running step, write the class and tick(), run the tests and bring back the output
- Learner asked "how can I check when tick is called?", which is the passive-object misconception again. Claude explained that a function body runs once per call (traced tests.cpp:15 call by call; DoorLock.tryCode analogy; on hardware the interrupt is the caller). No question asked; the build checkpoint (write the class and run the tests) is still open.
- Learner's first code attempt (asked "am I on the right track?"): class SoftTimer with tick(uint32_t counter) {counter++;} returning void, and the counter < period comparison inside start(), returning bool. counter is a global. No period/repeats/running members, no stop or isRunning. Claude ran the tests: answer.cpp compiles alone, but tests.cpp fails (no isRunning, tick() expects 1 arg and returns void).
- Claude's feedback: the step comments are on track but the code doesn't follow them. (1) The fire check belongs in tick, not start. (2) Concept: a parameter is a copy that shadows the global and disappears on return, so counter++ is lost. A global counter would also be shared by every timer. State goes in members, and tick takes no args. (3) Only 1 of the 4 confirmed stored items exists; start must save period and repeat into members (the unused-parameter warning points at this).
- Now asked: write start() steps as comments (what it sets each member to), then rewrite the class, run the tests and bring back the output
- Previous: the stored-state design was confirmed by the learner (Confirm and continue) and recorded in project-map.md
- Learner then said "Go ahead and write the answer using the logic I have". Claude wrote answer.cpp from their steps: counter++ per tick, fire on counter % period == 0, reset on fire, one-shot sets running off. Added from the spec: running check at the top of tick (Claude had flagged it), start resets the count, stop, isRunning const. Members named with a trailing _ so they don't shadow start's parameters. All 8 tests passed.
- Not resolved by the learner: whether % is still needed after reset-on-fire (Claude kept their %, and noted that == is equivalent and avoids a divide).
- No decision pending for drill 23.
- After reading the code, the learner said in their own words: "Because it is a class you can assign a timer to anything. You call SoftTimer t and then t.start and then tick is in the main loop." This states per-object state and the caller-driven tick model. It was stated after seeing Claude's code, not yet applied in code they wrote themselves.

## RTOS ticks and software timers

- Introduced (Claude explained): system tick as a periodic hardware interrupt; software timer as "fire after N ticks"; one-shot vs periodic; in the drill, tests call tick() in place of the interrupt.
- Introduced (Claude explained): where to start: the interface is fixed by the spec and tests, then decide the stored state, then each function becomes a small change to that state.
- Introduced (Claude explained): start's bool = repeat (one-shot vs periodic) is separate from tick()'s return value (true = fired this tick); traced start(3, false) tick by tick and contrasted it with start(3, true).
- Introduced (Claude explained): stop() disarms the timer, and later ticks do nothing until start is called again. Traced example 3 (start(2, true), tick, stop, 3 ticks) and gave the "cancel a timeout" use case. Learner said they now understand what the arguments mean.
- Demonstrated reasoning (learner): identified the four things the timer must store (period, repeat flag, tick count, running/stopped), and described counting up to the period and repeating if periodic.
- Needs reinforcement: learner first read start(3, false) as "true true false true true", mixing up the repeat flag and tick()'s return values. Their later answer used the flag correctly; not yet confirmed with a full trace.
- Introduced (Claude explained): unsigned overflow wraps to 0 (defined behavior in C++); a 32-bit tick count at 1 ms wraps after ~49.7 days; links to drill 19.
- Demonstrated reasoning (learner): proposed a per-call counter with a modulus check, a valid periodic rule and their own idea. After the wraparound was flagged, came up with resetting the count on fire themselves. Reasoned that a one-shot stops and waits for a new start.
- Needs reinforcement: event-driven / passive objects. Came up twice: a for loop inside tick(), then "how can I check when tick is called?". Claude explained that the caller loops, the function body runs once per call, and tick() does O(1) work per call. Check whether their written tick() reflects this.
- Developing: how member functions share state. Learner described tick as needing to "check if it's been stopped" during counting.

## C++ classes

- Introduced (Claude explained, DoorLock example): member variables as the object's state, default member initializers, public vs private, member functions with parameters, const member functions (needed for tests.cpp:31-32), including <cstdint> for uint32_t, the semicolon after the class.
- First attempt (drill 23): class syntax right (public:, member functions with parameters, trailing semicolon). State kept in a global and passed as a parameter rather than in members.
- Introduced (Claude explained): parameters are copies and shadow outer names; members persist between calls and are per-object.
- Learner asked why the private member block exists. Claude explained: it's the object's memory (their four stored items), private means only member functions can change it, default values make a new timer stopped and defined, position in the class doesn't matter, and period_ = 0 is safe because tick checks running_ first.
- Learner summarized: "Private block initializes them and makes it so that they cannot be updated outside of the class." Access part correct. Conflated private with initialization; Claude separated them (private = access, `= 0` = default member initializer, works in public too).
- Introduced (Claude explained, Point example compiled with drill flags): struct syntax; struct and class differ only in default access (struct public, class private); convention is struct for plain data bundles, class when members must be protected; brace initialization Point b{5, 7}.
- Needs reinforcement: where state lives between calls (members vs parameters/globals), which ties to the passive-object point in the RTOS section.
