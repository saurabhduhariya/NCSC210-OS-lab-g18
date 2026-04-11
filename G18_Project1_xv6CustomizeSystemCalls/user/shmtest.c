#include "kernel/types.h"
#include "user/user.h"

/*
 * shmtest.c - Shared Memory Test
 *
 * Demonstrates shared memory between a parent and child process:
 *   1. Parent creates a shared memory segment with shmget().
 *   2. Parent attaches it with shmat() and writes a value.
 *   3. Parent forks a child.
 *   4. Child attaches the same segment and reads the value.
 *   5. Child writes a reply, then detaches and exits.
 *   6. Parent reads the reply, detaches, and exits.
 */

#define SHM_KEY  42
#define SHM_SIZE 4096

int
main(void)
{
  // Step 1: create/get shared memory segment
  int id = shmget(SHM_KEY, SHM_SIZE);
  if (id < 0) {
    printf("shmget failed\n");
    exit(1);
  }
  printf("shmget: segment id = %d\n", id);

  // Step 2: attach in parent and write initial value
  int *shm = (int *)shmat(id);
  if ((uint64)shm == (uint64)-1) {
    printf("shmat failed in parent\n");
    exit(1);
  }
  shm[0] = 1234;
  printf("parent wrote: %d\n", shm[0]);

  // Step 3: fork child
  int pid = fork();
  if (pid < 0) {
    printf("fork failed\n");
    exit(1);
  }

  if (pid == 0) {
    // --- Child ---
    int *cshm = (int *)shmat(id);
    if ((uint64)cshm == (uint64)-1) {
      printf("shmat failed in child\n");
      exit(1);
    }
    printf("child read:  %d\n", cshm[0]);
    // Write a reply
    cshm[0] = 5678;
    printf("child wrote: %d\n", cshm[0]);
    shmdt(id, cshm);
    exit(0);
  } else {
    // --- Parent ---
    wait(0);
    printf("parent read after child: %d\n", shm[0]);
    shmdt(id, shm);
    printf("shared memory test passed!\n");
    exit(0);
  }
}
