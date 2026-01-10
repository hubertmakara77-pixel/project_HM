# Network Link Emulator

A C++ simulation tool designed to emulate network link behavior and introduce various transmission disturbances. The project simulates packet transmission between nodes and allows testing how protocols or applications might behave under poor network conditions.

## Features

The emulator supports a chain of disturbances that can be applied to packets:

- **Latency (Delay):** Simulates network lag by adding randomized time delays to packets.
- **Packet Loss (Drop):** Simulates unstable connections by randomly dropping packets based on a probability factor.
- **Data Corruption (Tamper):** Simulates transmission errors by modifying packet payload.
- **Packet Duplication:** Simulates scenarios where a receiver gets the same frame twice.
- **Bandwidth Throttling:** Simulates limited link speed; delay is calculated based on the size of the data payload.

## Technologies

- **Language:** C++17
- **Build System:** CMake
- **Memory Management:** Modern C++ Smart Pointers (`std::shared_ptr`, `std::make_shared`) ensuring **RAII** and **Exception Safety** (no memory leaks).
- **Design Patterns:** Strategy Pattern / Chain of Responsibility (for applying network effects).

## How to Build and Run

To build the project, you need a C++ compiler (like G++ or MSVC) and CMake installed.

### 1. Clone or Download

```bash
git clone [https://github.com/hubertmakara77-pixel/project_HM.git](https://github.com/hubertmakara77-pixel/project_HM.git)
cd project_HM

# Create build directory
mkdir build
cd build

# Configure project
cmake ..

# Compile
cmake --build .

# On Windows
./Program.exe

# On Linux/macOS
./Program

Author
Hubert Makara
```
