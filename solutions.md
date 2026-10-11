# Reference solutions

Open only after you have tried a drill. Each one passes its tests.

## 01 Swap and reverse with pointers

```cpp
#include <cstddef>

void swapInts(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverseArray(int* arr, std::size_t len) {
    if (len < 2) return;
    std::size_t i = 0;
    std::size_t j = len - 1;
    while (i < j) {
        swapInts(&arr[i], &arr[j]);
        ++i;
        --j;
    }
}
```

## 02 Count the set bits

```cpp
#include <cstdint>

int countSetBits(uint32_t x) {
    int count = 0;
    while (x != 0) {
        count += static_cast<int>(x & 1u);
        x >>= 1;
    }
    return count;
}
```

## 03 Binary search

```cpp
int binarySearch(const int* arr, int len, int target) {
    int lo = 0;
    int hi = len - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
```

## 04 XOR checksum

```cpp
#include <cstddef>
#include <cstdint>

uint8_t xorChecksum(const uint8_t* data, size_t len) {
    uint8_t sum = 0;
    for (size_t i = 0; i < len; ++i) {
        sum ^= data[i];
    }
    return sum;
}

bool isValidPacket(const uint8_t* data, size_t len) {
    if (len < 2) return false;
    return xorChecksum(data, len - 1) == data[len - 1];
}
```

## 05 Reverse a linked list

```cpp
struct Node {
    int value;
    Node* next;
};

Node* reverseList(Node* head) {
    Node* prev = nullptr;
    while (head != nullptr) {
        Node* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}
```

## 06 Distinct words in order

```cpp
#include <string>
#include <unordered_set>
#include <vector>

std::vector<std::string> distinctWords(const std::string& line) {
    std::vector<std::string> out;
    std::unordered_set<std::string> seen;
    std::string word;
    for (char ch : line) {
        if (ch == ' ') {
            if (!word.empty() && seen.insert(word).second) out.push_back(word);
            word.clear();
        } else {
            word += ch;
        }
    }
    if (!word.empty() && seen.insert(word).second) out.push_back(word);
    return out;
}
```

## 07 Largest element template

```cpp
#include <cstddef>
#include <iostream>

template <typename T>
T largest(const T* arr, std::size_t len) {
    T best = arr[0];
    for (std::size_t i = 1; i < len; ++i) {
        if (best < arr[i]) best = arr[i];
    }
    return best;
}

int main() {
    const int ints[] = {3, 9, 2, 7, 5};
    const double doubles[] = {1.5, -2.0, 4.25, 0.0};
    std::cout << largest(ints, 5) << '\n';
    std::cout << largest(doubles, 4) << '\n';
    return 0;
}
```

## 08 Register mode field

```cpp
#include <cstdint>

constexpr uint32_t MODE_SHIFT = 4u;
constexpr uint32_t MODE_MASK = 0x7u << MODE_SHIFT;

uint32_t getMode(uint32_t reg) {
    return (reg & MODE_MASK) >> MODE_SHIFT;
}

uint32_t setMode(uint32_t reg, uint32_t mode) {
    return (reg & ~MODE_MASK) | ((mode << MODE_SHIFT) & MODE_MASK);
}
```

## 09 Pack a CAN frame

```cpp
#include <cstdint>

struct CanFrame {
    uint32_t id;
    uint8_t len;
    uint8_t data[8];
};

CanFrame packMotorStatus(uint16_t speed, int8_t temperature) {
    CanFrame f{};
    f.id = 0x123;
    f.len = 3;
    f.data[0] = static_cast<uint8_t>(speed & 0xFFu);
    f.data[1] = static_cast<uint8_t>((speed >> 8) & 0xFFu);
    f.data[2] = static_cast<uint8_t>(temperature);
    return f;
}

bool unpackMotorStatus(const CanFrame& f, uint16_t& speed, int8_t& temperature) {
    if (f.id != 0x123 || f.len != 3) return false;
    speed = static_cast<uint16_t>(f.data[0] | (f.data[1] << 8));
    temperature = static_cast<int8_t>(f.data[2]);
    return true;
}
```

## 10 Fixed-size byte queue

```cpp
#include <cstddef>
#include <cstdint>

class ByteQueue {
public:
    bool push(uint8_t byte) {
        if (count_ == kCapacity) return false;
        buf_[tail_] = byte;
        tail_ = (tail_ + 1) % kCapacity;
        ++count_;
        return true;
    }

    bool pop(uint8_t& out) {
        if (count_ == 0) return false;
        out = buf_[head_];
        head_ = (head_ + 1) % kCapacity;
        --count_;
        return true;
    }

    size_t size() const { return count_; }

private:
    static constexpr size_t kCapacity = 16;
    uint8_t buf_[kCapacity] = {};
    size_t head_ = 0;
    size_t tail_ = 0;
    size_t count_ = 0;
};
```

## 11 Moving average filter

```cpp
#include <cstddef>
#include <cstdint>

class MovingAverage {
public:
    void add(int16_t sample) {
        if (count_ == kWindow) {
            sum_ -= samples_[next_];
        } else {
            ++count_;
        }
        samples_[next_] = sample;
        sum_ += sample;
        next_ = (next_ + 1) % kWindow;
    }

    double average() const {
        if (count_ == 0) return 0.0;
        return static_cast<double>(sum_) / static_cast<double>(count_);
    }

private:
    static constexpr size_t kWindow = 8;
    int16_t samples_[kWindow] = {};
    int32_t sum_ = 0;
    size_t count_ = 0;
    size_t next_ = 0;
};
```

## 12 Parse a key=value line

```cpp
#include <string>

bool parseKeyValue(const std::string& line, std::string& key, int& value) {
    const std::size_t eq = line.find('=');
    if (eq == std::string::npos || eq == 0) return false;
    std::size_t i = eq + 1;
    bool negative = false;
    if (i < line.size() && line[i] == '-') {
        negative = true;
        ++i;
    }
    if (i >= line.size()) return false;
    int result = 0;
    for (; i < line.size(); ++i) {
        const char c = line[i];
        if (c < '0' || c > '9') return false;
        result = result * 10 + (c - '0');
    }
    key = line.substr(0, eq);
    value = negative ? -result : result;
    return true;
}
```

## 13 Motor controller states

```cpp
#include <iostream>

enum class State { Idle, Running, Fault };
enum class Event { Start, Stop, EStop, Reset };

State nextState(State s, Event e) {
    if (e == Event::EStop) return State::Fault;
    switch (s) {
    case State::Idle:    return e == Event::Start ? State::Running : s;
    case State::Running: return e == Event::Stop ? State::Idle : s;
    case State::Fault:   return e == Event::Reset ? State::Idle : s;
    }
    return s;
}

const char* stateName(State s) {
    switch (s) {
    case State::Idle:    return "Idle";
    case State::Running: return "Running";
    case State::Fault:   return "Fault";
    }
    return "?";
}

int main() {
    const Event events[] = {Event::Start, Event::Stop, Event::Start, Event::EStop, Event::Start, Event::Reset};
    State s = State::Idle;
    for (Event e : events) {
        s = nextState(s, e);
        std::cout << stateName(s) << '\n';
    }
    return 0;
}
```

## 14 Sensor class hierarchy

```cpp
#include <memory>
#include <vector>

class Sensor {
public:
    virtual ~Sensor() = default;
    virtual double read() const = 0;
};

class TemperatureSensor : public Sensor {
public:
    explicit TemperatureSensor(int count) : count_(count) {}
    double read() const override { return count_ * 0.1 - 50.0; }
private:
    int count_;
};

class PressureSensor : public Sensor {
public:
    explicit PressureSensor(double kpa) : kpa_(kpa) {}
    double read() const override { return kpa_; }
private:
    double kpa_;
};

double averageReading(const std::vector<std::unique_ptr<Sensor>>& sensors) {
    if (sensors.empty()) return 0.0;
    double sum = 0.0;
    for (const auto& s : sensors) {
        sum += s->read();
    }
    return sum / static_cast<double>(sensors.size());
}
```

## 15 Owning buffer with RAII

```cpp
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <utility>

class Buffer {
public:
    explicit Buffer(std::size_t size) : size_(size), data_(std::make_unique<uint8_t[]>(size)) {}
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    Buffer(Buffer&&) = default;
    Buffer& operator=(Buffer&&) = default;

    std::size_t size() const { return size_; }
    uint8_t& operator[](std::size_t i) { return data_[i]; }

private:
    std::size_t size_;
    std::unique_ptr<uint8_t[]> data_;
};

int main() {
    Buffer a(64);
    a[0] = 0xAA;
    Buffer b = std::move(a);
    std::cout << static_cast<int>(b[0]) << '\n';
    return 0;
}
```

## 16 Bit helpers

```cpp
#include <cstdint>

uint32_t setBit(uint32_t reg, unsigned int bit) { return reg | (1u << bit); }
uint32_t clearBit(uint32_t reg, unsigned int bit) { return reg & ~(1u << bit); }
uint32_t toggleBit(uint32_t reg, unsigned int bit) { return reg ^ (1u << bit); }
bool isBitSet(uint32_t reg, unsigned int bit) { return ((reg >> bit) & 1u) != 0u; }
```

## 17 Byte order helpers

```cpp
#include <cstdint>

uint16_t swap16(uint16_t v) {
    return static_cast<uint16_t>((v >> 8) | (v << 8));
}

uint32_t swap32(uint32_t v) {
    return ((v & 0x000000FFu) << 24) |
           ((v & 0x0000FF00u) << 8)  |
           ((v & 0x00FF0000u) >> 8)  |
           ((v & 0xFF000000u) >> 24);
}

uint32_t readBigEndian32(const uint8_t* b) {
    return (static_cast<uint32_t>(b[0]) << 24) |
           (static_cast<uint32_t>(b[1]) << 16) |
           (static_cast<uint32_t>(b[2]) << 8)  |
            static_cast<uint32_t>(b[3]);
}

void writeLittleEndian32(uint8_t* out, uint32_t v) {
    out[0] = static_cast<uint8_t>(v & 0xFFu);
    out[1] = static_cast<uint8_t>((v >> 8) & 0xFFu);
    out[2] = static_cast<uint8_t>((v >> 16) & 0xFFu);
    out[3] = static_cast<uint8_t>((v >> 24) & 0xFFu);
}
```

## 18 Saturating math and ADC scaling

```cpp
#include <cstdint>

int16_t satAdd16(int16_t a, int16_t b) {
    const int32_t sum = static_cast<int32_t>(a) + static_cast<int32_t>(b);
    if (sum > INT16_MAX) return INT16_MAX;
    if (sum < INT16_MIN) return INT16_MIN;
    return static_cast<int16_t>(sum);
}

uint32_t adcToMillivolts(uint16_t count) {
    uint32_t c = count > 4095u ? 4095u : count;
    return (c * 3300u + 4095u / 2u) / 4095u;
}
```

## 19 Tick counter wraparound

```cpp
#include <cstdint>

uint32_t elapsedTicks(uint32_t now, uint32_t start) {
    return now - start;
}

bool hasTimedOut(uint32_t now, uint32_t start, uint32_t timeout) {
    return elapsedTicks(now, start) >= timeout;
}
```

## 20 Button debouncer

```cpp
class Debouncer {
public:
    explicit Debouncer(unsigned int samples) : needed_(samples == 0 ? 1 : samples) {}

    bool update(bool raw) {
        if (raw == stable_) {
            count_ = 0;
            return stable_;
        }
        if (++count_ >= needed_) {
            stable_ = raw;
            count_ = 0;
            if (stable_) pressed_ = true;
        }
        return stable_;
    }

    bool pressedEvent() {
        const bool event = pressed_;
        pressed_ = false;
        return event;
    }

private:
    unsigned int needed_;
    unsigned int count_ = 0;
    bool stable_ = false;
    bool pressed_ = false;
};
```

## 21 CRC-8 checksum

```cpp
#include <cstddef>
#include <cstdint>

uint8_t crc8(const uint8_t* data, size_t len) {
    uint8_t crc = 0x00;
    for (size_t i = 0; i < len; ++i) {
        crc ^= data[i];
        for (int bit = 0; bit < 8; ++bit) {
            if (crc & 0x80u) crc = static_cast<uint8_t>((crc << 1) ^ 0x07u);
            else crc = static_cast<uint8_t>(crc << 1);
        }
    }
    return crc;
}
```

## 22 Serial frame parser

```cpp
#include <cstddef>
#include <cstdint>

class FrameParser {
public:
    bool feed(uint8_t byte) {
        switch (state_) {
        case State::WaitStart:
            if (byte == 0xAA) state_ = State::Length;
            return false;
        case State::Length:
            if (byte > kMaxPayload) { state_ = State::WaitStart; return false; }
            expected_ = byte;
            received_ = 0;
            checksum_ = byte;
            state_ = expected_ == 0 ? State::Checksum : State::Payload;
            return false;
        case State::Payload:
            work_[received_++] = byte;
            checksum_ ^= byte;
            if (received_ == expected_) state_ = State::Checksum;
            return false;
        case State::Checksum:
            state_ = State::WaitStart;
            if (byte != checksum_) return false;
            for (size_t i = 0; i < expected_; ++i) payload_[i] = work_[i];
            length_ = expected_;
            return true;
        }
        return false;
    }

    size_t length() const { return length_; }
    const uint8_t* payload() const { return payload_; }

private:
    enum class State { WaitStart, Length, Payload, Checksum };
    static constexpr size_t kMaxPayload = 16;
    State state_ = State::WaitStart;
    uint8_t work_[kMaxPayload] = {};
    uint8_t payload_[kMaxPayload] = {};
    size_t expected_ = 0;
    size_t received_ = 0;
    size_t length_ = 0;
    uint8_t checksum_ = 0;
};
```

## 23 Software timer

```cpp
#include <cstdint>

class SoftTimer {
public:
    void start(uint32_t periodTicks, bool periodic) {
        period_ = periodTicks == 0 ? 1 : periodTicks;
        remaining_ = period_;
        periodic_ = periodic;
        running_ = true;
    }

    void stop() { running_ = false; }

    bool tick() {
        if (!running_) return false;
        if (--remaining_ != 0) return false;
        if (periodic_) remaining_ = period_;
        else running_ = false;
        return true;
    }

    bool isRunning() const { return running_; }

private:
    uint32_t period_ = 0;
    uint32_t remaining_ = 0;
    bool periodic_ = false;
    bool running_ = false;
};
```

## 24 Event group bits

```cpp
#include <cstdint>

class EventGroup {
public:
    void setBits(uint32_t mask) { bits_ |= mask; }
    void clearBits(uint32_t mask) { bits_ &= ~mask; }
    uint32_t getBits() const { return bits_; }

    bool waitAll(uint32_t mask, bool clearOnExit) {
        if ((bits_ & mask) != mask) return false;
        if (clearOnExit) bits_ &= ~mask;
        return true;
    }

    bool waitAny(uint32_t mask, bool clearOnExit) {
        if ((bits_ & mask) == 0u) return false;
        if (clearOnExit) bits_ &= ~mask;
        return true;
    }

private:
    uint32_t bits_ = 0;
};
```

## 25 Rate monotonic check

```cpp
#include <cmath>
#include <cstddef>
#include <cstdint>

double utilization(const uint32_t* wcet, const uint32_t* period, size_t n) {
    double u = 0.0;
    for (size_t i = 0; i < n; ++i) {
        u += static_cast<double>(wcet[i]) / static_cast<double>(period[i]);
    }
    return u;
}

bool rmsSchedulable(const uint32_t* wcet, const uint32_t* period, size_t n) {
    if (n == 0) return true;
    const double k = static_cast<double>(n);
    const double bound = k * (std::pow(2.0, 1.0 / k) - 1.0);
    return utilization(wcet, period, n) <= bound + 1e-12;
}
```

## 26 Pick the next task

```cpp
#include <cstddef>

enum class TaskState { Ready, Blocked, Suspended };

struct Task {
    int priority;
    TaskState state;
};

int pickNext(const Task* tasks, size_t count, int lastRun) {
    bool found = false;
    int best = 0;
    for (size_t i = 0; i < count; ++i) {
        if (tasks[i].state == TaskState::Ready && (!found || tasks[i].priority > best)) {
            best = tasks[i].priority;
            found = true;
        }
    }
    if (!found) return -1;
    const int n = static_cast<int>(count);
    for (int step = 1; step <= n; ++step) {
        const int idx = ((lastRun + step) % n + n) % n;
        if (tasks[idx].state == TaskState::Ready && tasks[idx].priority == best) return idx;
    }
    return -1;
}
```

## 27 Counting semaphore

```cpp
#include <cstddef>

class CountingSemaphore {
public:
    CountingSemaphore(unsigned int initial, unsigned int maximum)
        : count_(initial > maximum ? maximum : initial), max_(maximum) {}

    bool tryTake(int taskId) {
        if (count_ > 0) {
            --count_;
            return true;
        }
        if (waiting_ < kMaxWaiters) {
            waiters_[(head_ + waiting_) % kMaxWaiters] = taskId;
            ++waiting_;
        }
        return false;
    }

    int give() {
        if (waiting_ > 0) {
            const int id = waiters_[head_];
            head_ = (head_ + 1) % kMaxWaiters;
            --waiting_;
            return id;
        }
        if (count_ < max_) ++count_;
        return -1;
    }

    unsigned int count() const { return count_; }
    size_t waiting() const { return waiting_; }

private:
    static constexpr size_t kMaxWaiters = 8;
    unsigned int count_;
    unsigned int max_;
    int waiters_[kMaxWaiters] = {};
    size_t head_ = 0;
    size_t waiting_ = 0;
};
```

## 28 ISR-to-task message queue

```cpp
#include <cstddef>

template <typename T, size_t N>
class MessageQueue {
public:
    bool sendFromIsr(const T& msg) {
        if (count_ == N) {
            ++dropped_;
            return false;
        }
        buf_[tail_] = msg;
        tail_ = (tail_ + 1) % N;
        ++count_;
        return true;
    }

    bool receive(T& out) {
        if (count_ == 0) return false;
        out = buf_[head_];
        head_ = (head_ + 1) % N;
        --count_;
        return true;
    }

    size_t size() const { return count_; }
    size_t dropped() const { return dropped_; }

private:
    T buf_[N] = {};
    size_t head_ = 0;
    size_t tail_ = 0;
    size_t count_ = 0;
    size_t dropped_ = 0;
};
```

## 29 Mutex with priority inheritance

```cpp
#include <cstddef>

struct Task {
    int id;
    int basePriority;
    int priority;
};

class PiMutex {
public:
    bool lock(Task& t) {
        if (owner_ == nullptr) {
            owner_ = &t;
            return true;
        }
        if (count_ < kMaxWaiters) waiters_[count_++] = &t;
        if (t.priority > owner_->priority) owner_->priority = t.priority;
        return false;
    }

    Task* unlock(Task& t) {
        if (owner_ != &t) return nullptr;
        t.priority = t.basePriority;
        if (count_ == 0) {
            owner_ = nullptr;
            return nullptr;
        }
        size_t best = 0;
        for (size_t i = 1; i < count_; ++i) {
            if (waiters_[i]->priority > waiters_[best]->priority) best = i;
        }
        Task* next = waiters_[best];
        for (size_t i = best + 1; i < count_; ++i) waiters_[i - 1] = waiters_[i];
        --count_;
        owner_ = next;
        return next;
    }

    Task* owner() const { return owner_; }

private:
    static constexpr size_t kMaxWaiters = 8;
    Task* owner_ = nullptr;
    Task* waiters_[kMaxWaiters] = {};
    size_t count_ = 0;
};
```
