**Course:** Operating System Security  
**Topic:** Inter-Process Communication (IPC) & Memory Isolation  

## 📋 Overview
This repository contains the deliverables for Assignment 1. It demonstrates the secure implementation of Inter-Process Communication (IPC) using unidirectional pipes and provides empirical proof of process memory isolation (Virtual Address Space & Copy-On-Write) using the `fork()` system call. System call tracing was conducted using `strace` to analyze user-mode to kernel-mode transitions.

## 📂 Repository Contents

*   📝 **`ipc_secure.c`** 
    *   C program demonstrating secure unidirectional IPC between a parent and child process using `pipe()` and `fork()`. Includes predefined payload validation.
*   📝 **`mem_isolation.c`** 
    *   C program demonstrating memory isolation. Proves that modifying stack and dynamically allocated (heap) memory in a child process does not affect the parent, despite sharing the exact same virtual memory addresses.
*   🔍 **`trace_ipc.txt`** 
    *   Raw `strace` output captured during the execution of `ipc_secure.c` (following child processes with `-f`).
*   🔍 **`trace_mem.txt`** 
    *   Raw `strace` output captured during the execution of `mem_isolation.c`.
*   📊 **`OS_Security_Assignment_1_Report.pdf`** 
    *   The complete assignment report containing execution screenshots, technical methodology, and a detailed defense of the underlying OS concepts (Copy-On-Write, Virtual Memory, and System Call routing).

## ⚙️ How to Compile and Run (Kali Linux / Ubuntu)

**1. Secure IPC Program:**
```bash
gcc ipc_secure.c -o ipc_secure
strace -f -o trace_ipc.txt ./ipc_secure
```

**2. Memory Isolation Program:**
```bash
gcc mem_isolation.c -o mem_isolation
strace -f -o trace_mem.txt ./mem_isolation
```

## 🧠 Key OS Concepts Demonstrated
*   **Virtual Address Spaces:** Proving that memory addresses printed via `%p` are virtual illusions, while physical RAM remains strictly isolated.
*   **Copy-On-Write (COW):** Demonstrating how the OS duplicates physical memory pages on-the-fly only when a process attempts a write operation.
*   **System Call Tracing:** Using `strace` to bridge the gap between high-level C code and kernel-level execution (e.g., mapping `fork()` to the `clone()` syscall).
*   **Process Synchronization:** Utilizing `wait()` to prevent zombie and orphan processes.
