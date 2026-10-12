# Firmware Drills

39 interview-style C++ problems with real tests, compiled by your own g++: embedded, RTOS and core C++, each labeled intro, easy, medium or hard.

## On a new device

Needs `git`, `bash` and `g++` (or clang as `CXX=clang++`).

```sh
git clone https://github.com/dishishshawn/Firmware-Drills.git
cd Firmware-Drills
bash .tools/run-tests.sh problems/cpp-core/easy/01-swap-and-reverse-with-pointers
```

- Linux: `sudo apt install g++` if missing.
- macOS: `xcode-select --install`. Tests run without the 4 s time limit unless `brew install coreutils`.
- Windows: use WSL.
- Browser only (Chromebook, iPad): open the repo in GitHub Codespaces (Code → Codespaces) and run the same command in its terminal.

## How to use

1. Open the repo in Zed: `zed .` from the repo root. No Zed? Run `bash .tools/run-tests.sh problems/<topic>/<level>/<NN-name>` in any terminal.
2. Open a problem's `answer.cpp`. The problem is in the comment at the top; write your code below it.
3. Run the task **drill: run tests**: `alt-shift-t` to pick it, then `alt-t` to rerun it after each change.
   **drill: compile only** checks syntax without running anything.
4. Errors print as `answer.cpp:line:col`. Ctrl-click one in the terminal to jump there.

Practice mode is on in this repo (`.zed/settings.json`): no autocomplete, no AI suggestions, no auto-closed brackets. Error squiggles are on.
Tests are built with AddressSanitizer and UBSan when your g++ has them, so bad pointers and overflows crash with a report instead of passing by luck.
Exceptions are off (`-fno-exceptions`), like many embedded builds.

Reference solutions are in `solutions.md`. Try first.

`main.cpp` is a scratch file; the **build & run** task compiles and runs whatever file is open.

## Keeping your progress

Your answers are the `answer.cpp` files, so save them with git:

```sh
git pull                      # before you start
git add -A && git commit -m "drill 24" && git push   # when you stop
```

## Problems

Folders are `problems/<topic>/<level>/<NN-name>`: topics `embedded`, `rtos`, `cpp-core` and `classes-and-structs`; levels `intro`, `easy`, `medium` and `hard`. Numbers stay global, so drill 23 is `problems/rtos/easy/23-software-timer`.

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

### Classes and structs

A ladder from intro to hard, all embedded or RTOS flavored. Do them in order: each one uses what the one before it taught.

| # | Problem | Level | Uses | Area | Checks |
|---|---|---|---|---|---|
| 30 | Describe an LED | intro | struct | embedded | unit tests |
| 31 | Count encoder pulses | intro | class | embedded | unit tests |
| 32 | Find the hottest reading | easy | struct with a member function | embedded | unit tests |
| 33 | PWM channel with a constructor | easy | class with a constructor | embedded | unit tests |
| 34 | Wake delayed tasks | medium | struct and enum class | RTOS | unit tests |
| 35 | Task watchdog | medium | class holding an array of structs | RTOS | unit tests |
| 36 | UART driver over a register struct | medium | register struct and driver class | embedded | unit tests |
| 37 | Critical section guard | hard | RAII, destructor, deleted copy | RTOS | unit tests |
| 38 | Typed mailbox | hard | class template | RTOS | unit tests |
| 39 | Timer service with callbacks | hard | function pointers in a struct array | RTOS | unit tests |
