#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
child_work(const char *name, int priority)
{
  setpriority(0, priority);
  printf("%s: pid=%d priority=%d\n", name, getpid(), priority);
  for(int i = 0; i < 8; i++) {
    printf("%s: iteration=%d\n", name, i);
    yield();
  }
  exit(0);
}

int
main(int argc, char *argv[])
{
  if(fork() == 0) {
    child_work("HIGH", 1);
  }

  if(fork() == 0) {
    child_work("LOW", 10);
  }

  wait(0);
  wait(0);
  printf("schedtest: finished\n");
  exit(0);
}
