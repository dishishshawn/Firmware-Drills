# Firmware Drills

29 interview-style C++ problems (embedded, RTOS, core C++) with real tests. The problems, runner and reference solutions are in [`drills/`](drills/README.md).

## On a new device

Needs `git`, `bash` and `g++` (or clang as `CXX=clang++`).

```sh
git clone https://github.com/dishishshawn/Firmware-Drills.git
cd Firmware-Drills/drills
bash .tools/run-tests.sh problems/01-swap-and-reverse-with-pointers
```

- Linux: `sudo apt install g++` if missing.
- macOS: `xcode-select --install`. Tests run without the 4 s time limit unless `brew install coreutils`.
- Windows: use WSL.
- Browser only (Chromebook, iPad): open the repo in GitHub Codespaces (Code → Codespaces) and run the same command in its terminal.

## Keeping your progress

Your answers are the `answer.cpp` files, so save them with git:

```sh
git pull                      # before you start
git add -A && git commit -m "drill 24" && git push   # when you stop
```

`main.cpp` at the root is a scratch file; the root `.zed/tasks.json` has a **build & run** task for it.
