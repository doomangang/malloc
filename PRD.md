## **Product Requirements Document: `ft_malloc`**

---

### **1. Introduction**

This document outlines the requirements for `ft_malloc`, a custom implementation of a dynamic memory allocation library. The goal is to create a library that can replace the standard C library's `malloc`, `realloc`, and `free` functions, providing efficient memory management with an emphasis on performance and careful resource handling. The library will be usable in existing programs without modification or recompilation.

---

### **2. Core Objective**

[cite_start]The primary objective of this project is to implement a dynamic memory allocation mechanism from the ground up[cite: 3]. [cite_start]This involves creating a library that provides the core functionalities of `malloc(3)`, `realloc(3)`, and `free(3)` using lower-level system calls for memory management[cite: 56].

---

### **3. Functional Requirements**

#### **3.1. Core Memory Management Functions**

The library must implement the following standard functions with behavior identical to their `libc` counterparts:

* [cite_start]**`void *malloc(size_t size)`**: This function will allocate a block of memory of the specified `size` in bytes[cite: 65]. It must return a pointer to the beginning of this allocated block. [cite_start]If an error occurs during allocation, it will return a `NULL` pointer[cite: 70].
* [cite_start]**`void free(void *ptr)`**: This function deallocates a previously allocated block of memory pointed to by `ptr`[cite: 68]. [cite_start]If `ptr` is `NULL`, the function will perform no action[cite: 69].
* **`void *realloc(void *ptr, size_t size)`**: This function will resize the memory block pointed to by `ptr` to the new `size`. It may return the same pointer if the block can be resized in place, or a new pointer if the block needed to be moved. [cite_start]If a new block is allocated, the data from the old block will be copied to the new one, and the old block will be freed[cite: 66, 67]. [cite_start]If an error occurs, it will return a `NULL` pointer[cite: 70].

#### **3.2. Memory Allocation Strategy**

[cite_start]To optimize performance and minimize system calls, memory will be managed using pre-allocated zones for different size categories[cite: 73, 74].

* [cite_start]**TINY Mallocs**: For small memory requests (from 1 to 'n' bytes), allocations will be served from pre-allocated "TINY" zones. [cite: 79]
* [cite_start]**SMALL Mallocs**: For medium-sized requests (from n+1 to 'm' bytes), allocations will be served from pre-allocated "SMALL" zones. [cite: 81]
* [cite_start]**LARGE Mallocs**: For requests larger than 'm' bytes, memory will be allocated directly using `mmap()` and will exist in its own dedicated memory zone[cite: 82].

[cite_start]*Note: The specific values for 'n', 'm', and the sizes of the TINY and SMALL zones (N and M) are to be determined by the development team to balance performance and memory usage.* [cite: 83]

#### **3.3. Memory Visualization**

A function must be provided to display the layout of the allocated memory zones:

* [cite_start]**`void show_alloc_mem()`**: This function will print a formatted representation of all allocated memory blocks, grouped by type (TINY, SMALL, LARGE) and ordered by address[cite: 84, 87]. [cite_start]The output should clearly show the start and end addresses of each block and the total allocated memory[cite: 88, 89, 90, 91, 92, 93, 94, 95, 96, 97].

---

### **4. Non-Functional Requirements**

#### **4.1. Performance**
The implementation should be performant by limiting the number of direct calls to `mmap()` and `munmap()`. [cite_start]Pre-allocating zones for TINY and SMALL requests is a key strategy to achieve this[cite: 73].

#### **4.2. Error Handling**
The functions must handle errors gracefully. [cite_start]Under no circumstances should the library cause undefined behavior, segmentation faults, or other crashes[cite: 40].

#### **4.3. Code Quality**
[cite_start]The code must be clean, well-organized, and easy to understand, even in the absence of a strict coding standard[cite: 39].

#### **4.4. Memory Alignment**
[cite_start]All memory returned by `malloc` must be properly aligned[cite: 99].

---

### **5. Technical Specifications**

#### **5.1. System Calls and Allowed Functions**

* [cite_start]**Memory Management**: The core of the memory management must be implemented using the `mmap(2)` and `munmap(2)` system calls for requesting and releasing memory from the operating system[cite: 71].
* [cite_start]**Page Size**: The size of the pre-allocated memory zones must be a multiple of the system's page size, which should be determined using `getpagesize()` on macOS or `sysconf(_SC_PAGESIZE)` on Linux[cite: 75].
* **Other Allowed Functions**: The project may use `getrlimit(2)` and functions from a custom `libft` library (e.g., `write(2)`). [cite_start]For the thread-safe bonus, functions from the `pthread` library are permitted[cite: 41, 42, 43, 44, 45, 48].
* [cite_start]**Prohibited Functions**: The standard library's `malloc` is not to be used for the internal workings of this library[cite: 72].

#### **5.2. Compilation and Build Process**

* [cite_start]**Makefile**: A `Makefile` is required and must compile the project into a shared library[cite: 26].
* **Library Naming**: The final library file must be named `libft_malloc_$HOSTTYPE.so`, where `$HOSTTYPE` is an environment variable. [cite_start]The `Makefile` must handle cases where this variable is not set[cite: 25, 28, 29].
* [cite_start]**Symbolic Link**: The `Makefile` must also create a symbolic link named `libft_malloc.so` that points to the compiled library file[cite: 33].

---

### **6. Bonus Features (Optional)**

[cite_start]The following features can be implemented for additional credit, but only if the mandatory part is fully functional[cite: 110, 111, 112].

* [cite_start]**Thread Safety**: Ensure that the memory allocation functions are safe to use in a multi-threaded environment, likely using mutexes from the `pthread` library[cite: 104]. [cite_start]A global variable for thread-safety is permitted[cite: 38].
* [cite_start]**Debugging Tools**: Implement functionality controlled by environment variables for debugging memory allocations[cite: 106].
* [cite_start]**Enhanced Visualization**: Create an extended version of `show_alloc_mem()`, such as `show_alloc_mem_ex()`, that provides more detailed information like allocation history or a hexadecimal dump of memory zones[cite: 107].
* [cite_start]**Memory Defragmentation**: Implement a mechanism to "defragment" freed memory to optimize memory usage[cite: 108].