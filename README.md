# TaskForge: Hierarchical Work Processing & Package Delivery System
**COS 214 Practical 4**

---

## 1. Overview
TaskForge is an enterprise logistics and package delivery processing engine written in modern C++11. It demonstrates the seamless collaboration of four Gang of Four (GoF) design patterns:
* **Composite Pattern**: Hierarchical warehouse containers (`CargoGroup`) and leaf parcels (`PackageItem`).
* **State Pattern**: Parcel lifecycle transitions (`OrderPlacedState`, `InTransitState`, `DeliveredState`, `FailedDeliveryState`).
* **Decorator Pattern**: Dynamic runtime package extensions (`ExpressShippingDecorator`, `InsuranceDecorator`).
* **Iterator Pattern**: Traversal-modification safe iteration (`SnapshotIterator`, `PriorityFilteredIterator`).

---

## 2. Docker Setup & Execution

### 2.1 Build Docker Image
```bash
docker build -t taskforge .
```

### 2.2 Run Application Directly in Docker (One-Step Execution)

Run the full build, execution, and test suite inside Docker with a single command:

* **Linux / macOS / WSL (Bash)**:
  ```bash
  docker run --rm -v "${PWD}:/app" taskforge make run
  ```

* **Windows PowerShell**:
  ```powershell
  docker run --rm -v "${PWD}:/app" taskforge make run
  ```

* **Windows Command Prompt (CMD)**:
  ```cmd
  docker run --rm -v "%cd%:/app" taskforge make run
  ```

---

### 2.3 Interactive Container Shell (Optional)

To open an interactive terminal shell inside the container:
```bash
docker run -it --rm -v "${PWD}:/app" taskforge bash
```
*Once inside the container shell (`root@...:/app#`), you can run `make run`, `valgrind --leak-check=full ./taskforge`, or `gdb ./taskforge`, and type `exit` when done.*

## 3. Compilation & Verification Commands (Inside Container)

### 3.1 Build Executable
```bash
make clean && make
```

### 3.2 Run Application Scenarios
```bash
./taskforge
```
*Or via Makefile shortcut:*
```bash
make run
```

### 3.3 Run Memory Leak Verification (Valgrind)
```bash
valgrind --leak-check=full --show-leak-kinds=all ./taskforge
```
*Expected Output: `All heap blocks were freed -- no leaks are possible (0 bytes in 0 blocks)`.*

### 3.4 Run Debugging Session (GDB)
```bash
gdb ./taskforge
```
*(gdb commands: `set pagination off`, `break main`, `run`, `next`, `print warehouse`, `continue`).*