# Inter-process Communication: Pipes and FIFOs (COMP.2560)

This repository explores different methods of **Inter-process Communication (IPC)** within a Linux environment, developed at the **University of Windsor**. It focuses on data transit between independent processes using Pipes and Named Pipes (FIFOs).

## 🛠️ Technical Implementation Details

### 1. Bidirectional FIFO Communication
* **Files:** `fifo_bidirectional_server.c` / `client.c`
* Implementation of full-duplex messaging where the server sends an acknowledgment (ACK) back to the client upon receiving data.

### 2. Process Coordination (Game Logic)
* **File:** `multi_process_game_fifo.c`
* A multi-process application where processes coordinate their turns and actions using FIFOs for synchronization.

### 3. Robust Error Handling (SIGPIPE)
* **File:** `sigpipe_handler_simulator.c`
* Simulates a "Broken Pipe" scenario (writing to a pipe with no reader) and implements a signal handler to catch `SIGPIPE` without terminating the process.

## 💻 Environment
* **Language:** C (POSIX)
* **OS:** Linux
* **Concepts:** Named Pipes (FIFOs), Signal Handlers, File Descriptors, and Process Synchronization.