# Project Map

## Purpose

29 interview-style C++ drills (embedded, RTOS, core C++), each with tests, run with the local g++.

## Requirements

- Each drill: write code below the problem comment in `problems/<NN-name>/answer.cpp`.
- Tests call the names the problem comment specifies.
- Exceptions are off (`-fno-exceptions`); C++17.
- RTOS drills model scheduler/semaphores/queues/timers as plain data structures, without threads.

## Components

- `problems/<NN-name>/answer.cpp`: the problem statement and the learner's code
- `problems/<NN-name>/tests.cpp` or `expected.txt`: unit tests, or the expected output
- `.tools/run-tests.sh`: compiles and runs one drill
- `.zed/tasks.json`: "drill: run tests" and "drill: compile only" tasks
- `.zed/settings.json`: practice mode (no autocomplete, LSP or AI suggestions)
- `solutions.md`: reference solutions (not to be shown unless asked)

## Main Flow

answer.cpp --(syntax check, -Wall -Wextra)--> OK?
--(run-tests.sh concatenates answer.cpp + tests.cpp, renames user main)--> unit.cpp
--(g++ -O1 with ASan+UBSan when available)--> prog --(4 s timeout)--> PASS|name / FAIL|name|detail lines

## Data and Trust Boundaries

Local only. No external services.

## Build and Deployment

- `bash .tools/run-tests.sh problems/<NN-name>` (verified in the script)
- Zed: alt-shift-t picks "drill: run tests", alt-t reruns it

## Unknowns

None for the tooling.

## Drill 23: SoftTimer (design confirmed, not implemented)

Stored state (learner's design, confirmed):
- period: ticks between fires (set by start)
- repeats: periodic or one-shot (set by start)
- ticks counted so far: counts up toward the period
- running: on/off (start turns on, stop turns off)

Unknown, to decide next: what happens to the count on firing, what start does to a count already in progress, what a one-shot changes after it fires. C++ types not chosen yet.
