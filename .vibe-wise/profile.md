# Learner Profile

Learning mode: active
Onboarding: complete

## Project

Situation: Existing (drill folder of independent C++ interview problems)
Building: Working through the drills; currently on 23-software-timer (first RTOS drill)
Codebase familiarity: Not specified (drills are independent problems)
Learning scope: The current drill and the concepts behind it; learner said "I want to understand it"

## Experience

Overall programming: Beginner (self-reported)
Stack familiarity: C++ Beginner; RTOS none (self-reported)

## Goals

Primary: Understand drill 23 (software timer) and how to start an RTOS-style problem
Capability goal: Not specified

## Preferences

Checkpoint frequency: Normal (default)
Question style: Open-ended (default)
Implementation style: Learner writes drill code by default; AI explains, gives feedback, and teaches concepts. On drill 23 the learner asked Claude to write answer.cpp from their logic.

## Strong Concepts

No demonstrated understanding recorded yet.

## Developing Concepts

- Caller-driven objects and per-object state (drill 23): explained it in their own words after reading the finished code; not yet applied in code they wrote.
- Pass by value vs by reference (drill 30): wrote Led& for functions that change the struct and const Led& for read-only, after tracing the copy. Applied in their own code; all tests pass.
- Member functions use the object's own state, and const member functions (drill 31): wrote PulseCounter with no parameters, private total, count() const; all tests pass.
- Pointers to structs and const-correct returns (drill 32): free function over an array of structs, size_t indexes, returns const Reading* or nullptr; all tests pass, no warnings. Needed two explanations for the return type.
- Constructors and private invariants (drill 33): constructor sets members, setDuty clamps into a private member, const getters, uint64_t widening against overflow; all tests pass. Still assigns in the body rather than an initializer list. If/else chaining needed a trace; fixed with early returns.

## Revisit

None recorded yet.
