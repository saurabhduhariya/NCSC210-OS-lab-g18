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