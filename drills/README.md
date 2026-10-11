# C++ drills

29 interview-style C++ problems with real tests, compiled by your own g++: embedded, RTOS and core C++, each labeled easy or medium.

## How to use

1. Open this folder in Zed: `zed drills` from the repo root (opening the repo root works too). No Zed? Run `bash .tools/run-tests.sh problems/<NN-name>` from this folder in any terminal.
2. Open a problem's `answer.cpp`. The problem is in the comment at the top; write your code below it.
3. Run the task **drill: run tests**: `alt-shift-t` to pick it, then `alt-t` to rerun it after each change.
   **drill: compile only** checks syntax without running anything.
4. Errors print as `answer.cpp:line:col`. Ctrl-click one in the terminal to jump there.

Practice mode is on in this folder (`.zed/settings.json`): no autocomplete, no live error squiggles, no AI suggestions, no auto-closed brackets.
Tests are built with AddressSanitizer and UBSan when your g++ has them, so bad pointers and overflows crash with a report instead of passing by luck.
Exceptions are off (`-fno-exceptions`), like many embedded builds.

Reference solutions are in `solutions.md`. Try first.

## Problems

Labels are in each folder's first comment line too, for example `[MEDIUM] [RTOS]`. RTOS problems model the scheduler, semaphores, queues and timers as plain data structures, so no threads are needed.

### Embedded

| # | Problem | Level | Checks |
|---|---|---|---|
| 02 | Count the set bits | easy | unit tests |
| 04 | XOR checksum | easy | unit tests |
| 08 | Register mode field | medium | unit tests |
| 09 | Pack a CAN frame | medium | unit tests |
| 10 | Fixed-size byte queue | medium | unit tests |
| 11 | Moving average filter | medium | unit tests |
| 13 | Motor controller states | medium | output |
| 16 | Bit helpers | easy | unit tests |
| 17 | Byte order helpers | easy | unit tests |
| 18 | Saturating math and ADC scaling | easy | unit tests |
| 19 | Tick counter wraparound | easy | unit tests |
| 20 | Button debouncer | medium | unit tests |
| 21 | CRC-8 checksum | medium | unit tests |
| 22 | Serial frame parser | medium | unit tests |

### RTOS

| # | Problem | Level | Checks |
|---|---|---|---|
| 23 | Software timer | easy | unit tests |
| 24 | Event group bits | easy | unit tests |
| 25 | Rate monotonic check | easy | unit tests |
| 26 | Pick the next task | medium | unit tests |
| 27 | Counting semaphore | medium | unit tests |
| 28 | ISR-to-task message queue | medium | unit tests |
| 29 | Mutex with priority inheritance | medium | unit tests |

### C++ core

| # | Problem | Level | Checks |
|---|---|---|---|
| 01 | Swap and reverse with pointers | easy | unit tests |
| 03 | Binary search | easy | unit tests |
| 05 | Reverse a linked list | easy | unit tests |
| 06 | Distinct words in order | easy | unit tests |
| 07 | Largest element template | easy | output |
| 12 | Parse a key=value line | medium | unit tests |
| 14 | Sensor class hierarchy | medium | unit tests |
| 15 | Owning buffer with RAII | medium | output |
