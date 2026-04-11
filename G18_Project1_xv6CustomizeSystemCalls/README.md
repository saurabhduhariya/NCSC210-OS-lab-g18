## xv6 System Call Implementation Project

### a. Analysis of Existing System Calls
Analyze the existing implementation of system calls within the xv6 operating system that are targeted for modification. This involves tracing the flow from user-space invocation (via `usys.S`) to the kernel-space handler (`syscall.c` and `sysproc.c` or `sysfile.c`).

### b. System Call Development
Modify or implement new system calls for at least **five** distinct functionalities. Potential areas of implementation include:
* **Process Creation:** Enhancing `fork` or implementing `clone`.
* **Inter-Process Communication (IPC):** Implementing shared memory, message queues, or pipes.
* **Threads:** Adding kernel-level support for lightweight processes.
* **Locks:** Implementing sleep locks or spinlocks accessible via system calls.
* **Signals:** Adding a basic signaling mechanism for process notification.

### c. User Program Demonstration
Create and integrate a new user-level program within the xv6 environment. This program must actively utilize the five new or modified system calls to demonstrate their functionality and correctness.

### d. Documentation
Provide comprehensive documentation for the project, including:
* Technical descriptions of the logic changes in the kernel.
* Instructions on how to compile and run the user program.
* A summary of the challenges faced during implementation.

---
**Note:** Ensure you attach screenshots of the successful execution and output of your user program within the documentation file.

---
## Project Status (3/5 Completed)

### ✅ Completed Functionalities
- [x] **Process Tracking:** Implemented `getppid` to get the parent process ID.
- [x] **Inter-Process Communication (IPC):** Implemented `send` and `recv` for message passing.
- [x] **Threads:** Implemented `clone` to provide kernel-level support for lightweight processes.

### ⏳ Remaining Functionalities
- [ ] **Locks:** Implement sleep locks or spinlocks accessible via system calls.
- [ ] **Signals:** Add a basic signaling mechanism for process notification.
- [ ] **Unified Demonstration Program:** Create a single user program that utilizes all 5 new system calls and outputs the results.
- [ ] **Documentation:** Write technical descriptions of kernel logic changes and challenges.

---
## Teammate Guide: How to Add a New System Call

To implement a new system call, you must modify files in both user-space and kernel-space. Follow this checklist:

### 1. User-Space Changes
* **`user/user.h`**: Add the C function prototype for your system call (e.g., `int mysys();`).
* **`user/usys.pl`**: Add an entry for the perl script to generate the assembly stub (e.g., `entry("mysys");`).
* **`user/mytest.c`**: Create a test program to demonstrate your new system call.
* **`Makefile`**: Add your test program (e.g., `$U/_mytest\`) to the `UPROGS` list so it gets compiled automatically.

### 2. Kernel-Space Changes
* **`kernel/syscall.h`**: Define a unique system call number at the bottom (e.g., `#define SYS_mysys 26`).
* **`kernel/syscall.c`**: 
    * Add the external declaration: `extern uint64 sys_mysys(void);`
    * Add it to the syscalls array: `[SYS_mysys] sys_mysys,`
* **`kernel/sysproc.c`** (or `sysfile.c`): Write the `sys_mysys(void)` wrapper function. Use `argint`, `argaddr`, etc., to safely extract arguments passed from user space.
* **`kernel/proc.c`** (and `kernel/defs.h`): If your system call requires complex process manipulation (like locks or signals), write the actual kernel function here and declare it in `defs.h`.

---
## Git Workflow Guide for Teammates

To avoid merge conflicts and organize our work, please follow this Git workflow for your tasks:

1. **Get the latest code from the main/master branch:**
   ```bash
   git checkout main
   git pull origin main
   ```

2. **Create a new branch for your feature:**
   ```bash
   git checkout -b feature/your-feature-name
   ```
   *(e.g., `git checkout -b feature/spinlock-syscall`)*

3. **Make your changes, then compile and test:**
   ```bash
   make clean
   make qemu
   ```

4. **Commit your changes securely:**
   ```bash
   git add .
   git commit -m "Add [feature]: Brief description of the syscall you added"
   ```

5. **Push your branch to the remote repository:**
   ```bash
   git push -u origin feature/your-feature-name
   ```

6. **Create a Pull Request:**
   Go to the GitHub/GitLab repository website and create a Pull Request from your `feature` branch into the `main` branch. Ping a teammate to review the code before merging.