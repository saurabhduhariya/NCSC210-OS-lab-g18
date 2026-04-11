#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// Define a simple stack for our thread to use
#define PGSIZE 4096
char thread_stack[PGSIZE];

// The function the new thread will execute
void thread_function() {
    printf("Hello from the new thread! My PID is %d\n", getpid());
    exit(0);
}

int main(void) {
    printf("Main thread: starting. My PID is %d\n", getpid());

    // We pass the TOP of the stack to the clone syscall.
    // In xv6, stacks grow downwards, so we add PGSIZE.
    int thread_id = clone(&thread_stack[PGSIZE]);

    if(thread_id < 0) {
        printf("Main thread: clone failed!\n");
        exit(1);
    } else if(thread_id == 0) {
        // We are inside the new thread!
        thread_function();
    } else {
        // We are still the main parent thread. We wait for our thread to finish.
        printf("Main thread: created a new thread with PID %d\n", thread_id);
        wait(0);
        printf("Main thread: child thread exited. Bye!\n");
    }

    exit(0);
}
