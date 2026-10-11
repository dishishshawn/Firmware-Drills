#!/usr/bin/env bash
# Compile one drill's answer.cpp with g++, then run its tests.
# Usage: bash run-tests.sh <problem folder>   (Zed's "drill: run tests" task passes the open file's folder)
set -u
dir="${1:-$PWD}"
cd "$dir" || { echo "Can't open $dir"; exit 1; }
if [ ! -f answer.cpp ]; then echo "Open a drill's answer.cpp first, then run the task."; exit 1; fi
CXX="${CXX:-g++}"
STD=(-std=c++17 -fno-exceptions)
work="$(mktemp -d)"
trap 'rm -rf "$work"' EXIT
# macOS has no `timeout` (Homebrew coreutils ships it as gtimeout); without either, run unlimited.
if command -v timeout >/dev/null; then limit() { timeout 4 "$@"; }
elif command -v gtimeout >/dev/null; then limit() { gtimeout 4 "$@"; }
else limit() { "$@"; }; fi

echo "\$ $CXX -std=c++17 -Wall -Wextra -fno-exceptions answer.cpp"
if ! "$CXX" "${STD[@]}" -Wall -Wextra -fsyntax-only answer.cpp; then
  echo
  echo "Fix the compile errors to run the tests."
  exit 1
fi
echo "Compiles."
echo

# Build with AddressSanitizer + UBSan when available, so bad pointers and overflows crash loudly.
build() { # build <source> <output>
  if "$CXX" "${STD[@]}" -O1 -g -w -fsanitize=address,undefined -fno-omit-frame-pointer "$1" -o "$2" 2> "$work/err"; then return 0; fi
  if grep -qiE "asan|ubsan|sanitizer" "$work/err"; then
    "$CXX" "${STD[@]}" -O1 -g -w "$1" -o "$2" 2> "$work/err" && return 0
  fi
  return 1
}

if [ -f tests.cpp ]; then
  {
    printf '#define main reps_user_main_\n#line 1 "answer.cpp"\n'
    cat answer.cpp
    printf '\n#undef main\n#line 1 "tests.cpp"\n'
    cat tests.cpp
  } > "$work/unit.cpp"
  if ! build "$work/unit.cpp" "$work/prog"; then
    echo "Your code compiles on its own, but the tests couldn't use it."
    echo "Check the names, parameter types and return types at the top of answer.cpp. g++ said:"
    echo
    cat "$work/err"
    exit 1
  fi
  ASAN_OPTIONS=detect_leaks=0 limit "$work/prog" > "$work/out" 2> "$work/stderr"
  status=$?
  pass=0; fail=0
  while IFS='|' read -r tag name detail; do
    case "$tag" in
      PASS) pass=$((pass + 1)); printf '  pass  %s\n' "$name" ;;
      FAIL) fail=$((fail + 1)); printf '  FAIL  %s: %s\n' "$name" "$detail" ;;
    esac
  done < "$work/out"
  if [ "$status" -eq 124 ]; then echo "  Stopped after 4 seconds. Look for a loop that never ends."
  elif [ "$status" -ne 0 ]; then echo "  The program crashed (exit status $status). Details:"; sed 's/^/    /' "$work/stderr" | head -n 40
  fi
  echo
  if [ "$fail" -eq 0 ] && [ "$pass" -gt 0 ] && [ "$status" -eq 0 ]; then echo "All $pass tests passed."; else echo "$pass passed, $fail failed."; exit 1; fi
else
  if ! build answer.cpp "$work/prog"; then cat "$work/err"; exit 1; fi
  ASAN_OPTIONS=detect_leaks=0 limit "$work/prog" > "$work/out" 2> "$work/stderr"
  status=$?
  norm() { awk '{ sub(/[ \t\r]+$/, ""); print }' "$1"; }
  if [ "$status" -eq 124 ]; then echo "Stopped after 4 seconds. Look for a loop that never ends."; exit 1; fi
  if [ "$status" -ne 0 ]; then echo "The program crashed (exit status $status):"; sed 's/^/  /' "$work/stderr" | head -n 40; fi
  if diff <(norm expected.txt) <(norm "$work/out") > "$work/diff"; then
    echo "Output matches."
  else
    echo "Output differs. Lines starting with < are expected, > are what your program printed:"
    sed -n '/^[<>]/p' "$work/diff"
    exit 1
  fi
fi
