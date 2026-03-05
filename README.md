# Embedded Mastery Kit

> A comprehensive, structured repository dedicated to mastering the core competencies of Firmware Engineering and Embedded Systems.

This repository serves as a practical, hands-on toolkit for exploring bare-metal programming, system architecture, and real-time operating systems. It is designed with modularity in mind, allowing each concept to be implemented, tested, and analyzed in isolation.

## 🗂️ Repository Structure

The code is divided into six progressive technical domains:

### 1. C Fundamentals (`01-c-fundamentals/`)
Core language mechanics critical for embedded environments.
* **Pointers:** Raw pointers, pointer arithmetic, and double pointers.
* **Function Pointers:** Callbacks and dispatch tables for decoupled code.
* **Keywords:** Proper usage of `static`, `volatile`, `const`, and `extern`.

### 2. Math & Bitwise Operations (`02-math-bitwise-operations/`)
Low-level bitwise and mathematical operations for embedded systems.
* **Bitwise Operations:** Setting, clearing, toggling, and reading specific bits using masks and shifts.
* **Optimized Operations:** Fast variable swapping, bit counting, and handling endianness.
* **Mathematical Operations:** Averaging, median, and other statistical calculations.

### 3. Algorithms & Data Structures (`03-algorithms-data-structures/`)
Memory-bounded implementations optimized for performance.
* **Data Structures:** Static and lock-free circular buffers, queues, stacks, linked lists, trees, and heaps.
* **Algorithms:** Searching, filtering, and data transformation, complete with Big O time and space complexity analysis.

### 4. Design Patterns (`04-design-patterns/`)
Scalable architectural approaches for firmware applications.
* **Architectural:** Finite State Machines (FSM), Behavior Trees, and the Observer pattern.
* **Creational & Structural:** Singleton, Factory, Hardware Abstraction Layers (HAL), Opaque pointers, and Adapter/Bridge patterns.

### 5. Communication Protocols (`05-communication-protocols/`)
Abstract interfaces and driver logic for standard serial buses.
* **I2C:** Master/slave driver implementations and state handling.
* **SPI:** Polling, interrupt-driven, and DMA-based transfer logic.
* **UART:** Integration with underlying ring buffers for reliable data streaming.

### 6. RTOS Fundamentals (`06-rtos-fundamentals/`)
Concurrency, synchronization, and task management (featuring implementations geared toward environments like Zephyr).
* **Scheduling:** Preemptive vs. cooperative scheduling, and handling priority inversion.
* **Kernel Primitives:** Safe usage of mutexes, semaphores, message queues, and thread management.

## 🛠️ Build System

This project is built using **CMake**. The modular structure allows individual components and test applications to be built independently without compiling the entire repository.

```bash
# Example build commands
mkdir build && cd build
cmake ..
make