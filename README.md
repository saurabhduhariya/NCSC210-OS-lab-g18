# NCSC210 Operating Systems Laboratory - Group G18

Repository for Group G18's project in the Operating Systems Laboratory (NCSC210) course.

## Team Members

* **24JE0689** - Satyavarapu Surya Sitha Harini Sreeja
* **24JE0690** - Saurabh Prajapat
* **24JE0691** - Shaik Zaheer Mushtaq
* **24JE0692** - Shalvi Kumari
* **24JE0693** - Shivam Chaudhary
* **24JE0694** - Shlok Radadia

## Who Did What

* **24JE0689 - Satyavarapu Surya Sitha Harini Sreeja**
    * [Project 1] Set up the xv6 project baseline and implemented `getppid` along with IPC syscalls (`send` and `recv`) for inter-process message passing.
    * [Project 2] Implemented the `g18_wc` utility for line, word, and byte counting, and integrated the initial shell and documentation structure.

* **24JE0690 - Saurabh Prajapat**
    * [Project 1] Implemented the `clone` system call for lightweight process creation and validated thread execution via `thtest`.
    * [Project 2] Set up the Project 2 architecture and implemented the `g18_ls` (with `-a`, `-l` flags) and `g18_mkdir` (with `-p` flag) utilities.

* **24JE0691 - Shaik Zaheer Mushtaq**
    * [Project 1] Implemented shared-memory system call pipeline (`shmget`, `shmat`, `shmdt`) for efficient cross-process data sharing.
    * [Project 2] Implemented the `g18_grep` utility with advanced pattern matching flags (`-i`, `-n`, `-c`, `-v`) and standard input support.

* **24JE0692 - Shalvi Kumari**
    * [Project 1] Implemented user-accessible lock system calls (`mylock_init`, `mylock_acquire`, `mylock_release`) to handle process synchronization functionality.
    * [Project 2] Implemented the `g18_cp` utility handling safe source-to-destination file copy operations and error checking.

* **24JE0693 - Shivam Chaudhary**
    * [Project 1] Implemented signal handling syscalls (`alarm_signal` and `sigreturn`) integrating kernel-side timers with user-space handlers.
    * [Project 2] Implemented `g18_touch` for timestamp manipulation/creation and `g18_cat` with standard input handling and line numbering (`-n`).

* **24JE0694 - Shlok Radadia**
    * [Project 1] Implemented scheduling system calls (`setpriority`, `getpriority`, `yield`) integrating dynamic priority adjustments directly into the xv6 scheduler.
    * [Project 2] Implemented `g18_rm` (with continuous and recursive `-r` file deletion) and `g18_mv` for move/rename operations.