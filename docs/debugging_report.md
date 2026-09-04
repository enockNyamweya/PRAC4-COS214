# Task 5

## 1. GDB Debugging Evidence (Breakpoints, Stepping & Inspection)

### Command Execution Log:
```gdb
$ gdb ./taskforge
GNU gdb (Ubuntu 15.1-1ubuntu1~24.04.1) 15.1
Reading symbols from ./taskforge...

(gdb) set pagination off
(gdb) break main
Breakpoint 1 at 0x6dcc: file main.cpp, line 22.

(gdb) run
Starting program: /mnt/c/Users/.../taskforge
Breakpoint 1, main () at main.cpp:22
22      int main(){

(gdb) next
23          cout<<"SCENARIO I: NORMAL DISPATCH & DECORATORS\n"<<endl;

(gdb) next
26          WorkUnit* warehouse=new CargoGroup("Johannesburg Main Warehouse");

(gdb) next
27          WorkUnit* hub=new CargoGroup("Air Freight Sector");

(gdb) next
31          warehouse->add(hub);

(gdb) print warehouse
$1 = (WorkUnit *) 0x5555555732b0

(gdb) continue
Continuing.
... Starting Warehouse Traversal & Execution
[CargoGroup] Processing Group: Air Freight Sector
[CargoGroup] Processing Group: Pallet A1
[PackageItem] Parcel (TRK-101: Electronics Parcel, Weight: 4.5kg)
```

---

## 2. Bug #1: Use-After-Free in Iterator Destructor

### A. Symptom
During Scenario II execution, calling `getName()` on an iterator's current item triggered an immediate runtime segmentation fault:
```text
SCENARIO II: DYNAMIC & MID-TRAVERSAL SAFETY
Segmentation fault (core dumped)
```

### B. Root Cause
In `SnapshotIterator::~SnapshotIterator()`, the destructor contained an aggressive deletion loop:
```cpp
// Buggy implementation in SnapshotIterator.cpp:
SnapshotIterator::~SnapshotIterator() {
    for (WorkUnit* ptr : snapshot) {
        delete ptr; // this frees live warehouse nodes!
    }
    snapshot.clear();
}
```
When `delete it1;` executed after Scenario I, `SnapshotIterator::~SnapshotIterator()` deleted all `WorkUnit*` instances referenced in its snapshot array. When Scenario II subsequently instantiated `it2` over `warehouse` and invoked `it2->currentItem()->getName()`, it attempted to access freed memory at address `0x555555573770`.

### C. GDB Debugging Evidence (Stack Trace)
```gdb
Program received signal SIGSEGV, Segmentation fault.
__memcpy_avx_unaligned_erms () at ../sysdeps/x86_64/multiarch/memmove-vec-unaligned-erms.S:342

(gdb) backtrace
#0  __memcpy_avx_unaligned_erms () at ../sysdeps/x86_64/multiarch/memmove-vec-unaligned-erms.S:342
#1  0x00007ffff7ea3876 in void std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_construct<char*>(char*, char*, std::forward_iterator_tag) () from /lib/x86_64-linux-gnu/libstdc++.so.6
#2  0x000055555555ad11 in WorkUnit::getName[abi:cxx11]() const (this=0x555555573770) at WorkUnit.cpp:10
#3  0x000055555555b46e in main () at main.cpp:65
```

### D. Correction
The destructor was updated so the iterator merely drops its references without attempting to manage object lifetimes (since composite containers own the nodes):
```cpp
// Corrected implementation in SnapshotIterator.cpp:
SnapshotIterator::~SnapshotIterator() {
    snapshot.clear(); // Safely clears pointer references only
}
```

---

## 3. Bug #2: Double-Free Heap Corruption in Iterator Cleanup

### A. Symptom
During Scenario III, after finishing filtered iteration, calling `delete baseIt;` crashed the application:
```text
SCENARIO III: STATES LIFECYCLE & USING FILTERED ITERATOR
...Priority Filtered Iteration
Segmentation fault (core dumped)
```

### B. Root Cause
In `PriorityFilteredIterator::~PriorityFilteredIterator()`, the wrapper destructor already frees its inner iterator:
```cpp
PriorityFilteredIterator::~PriorityFilteredIterator() {
    delete inneriterator; // Deletes baseIt automatically
}
```
In `main.cpp`, the driver code called `delete priorityIt;` followed by `delete baseIt;`. Deleting `baseIt` a second time caused heap memory corruption.

### C. GDB Debugging Evidence (Stack Trace)
```gdb
Program received signal SIGSEGV, Segmentation fault.
0x000055555555b9d0 in main () at main.cpp:106
106         delete baseIt;

(gdb) backtrace
#0  0x000055555555b9d0 in main () at main.cpp:106
```

### D. Correction
Removed `delete baseIt;` from `main.cpp`, delegating inner iterator cleanup entirely to `PriorityFilteredIterator::~PriorityFilteredIterator()`.

---

## 4. Valgrind Memory Verification 

### Terminal Command & Full Execution Log:
```bash
$ valgrind --leak-check=full --show-leak-kinds=all ./taskforge
==40657== Memcheck, a memory error detector
==40657== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==40657== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==40657== Command: ./taskforge
==40657== 
SCENARIO I: NORMAL DISPATCH & DECORATORS

... Starting Warehouse Traversal & Execution

[CargoGroup] Processing Group: Air Freight Sector
[CargoGroup] Processing Group: Pallet A1
[PackageItem] Parcel (TRK-101: Electronics Parcel, Weight: 4.5kg)
Order Placed, Dispatching...
[Express] The priority level for Electronics Parcel is: 1
The express is R50
[Insurance] The policy number is: POL-991
The insurance amount is R500
[PackageItem] Parcel (TRK-102: Clothing Parcel, Weight: 2kg)
Order Placed, Dispatching...


SCENARIO II: DYNAMIC & MID-TRAVERSAL SAFETY
Step 1 visiting: Air Freight Sector


[DYNAMIC CHANGE] Adding new Pallet B2 and moving parcel...

... Resuming Traversal to the end...

SCENARIO III: STATES LIFECYCLE & USING FILTERED ITERATOR
[PackageItem] Parcel (TRK-999: Test Parcel, Weight: 1.5kg)
Order Placed, Dispatching...
[PackageItem] Parcel (TRK-999: Test Parcel, Weight: 1.5kg)
Package has already been dispatched.
[PackageItem] Parcel (TRK-999: Test Parcel, Weight: 1.5kg)
Package has already been dispatched.
...Priority Filtered Iteration

Execution complete
==40657== 
==40657== HEAP SUMMARY:
==40657==     in use at exit: 0 bytes in 0 blocks
==40657==   total heap usage: 41 allocs, 41 frees, 75,982 bytes allocated
==40657== 
==40657== All heap blocks were freed -- no leaks are possible
==40657== 
==40657== For lists of detected and suppressed errors, rerun with: -s
==40657== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

---
**Verification Conclusion**: The final application achieves 0 memory leaks across all 41 dynamic heap allocations.
