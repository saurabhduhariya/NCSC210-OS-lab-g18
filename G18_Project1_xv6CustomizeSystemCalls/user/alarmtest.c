#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void periodic_handler() {
  printf("alarm!\n");
  sigreturn();
}

void test_alarm() {
  int interval = 10;
  printf("test_alarm: starting\n");
  alarm_signal(interval, periodic_handler);
  for (int i = 0; i < 50; i++) {
    if (i % 10 == 0) printf("test_alarm: loop %d\n", i);
    // busy wait
    for (int j = 0; j < 10000000; j++) {
      __asm__("nop");
    }
  }
  alarm_signal(0, 0); // turn off
  printf("test_alarm: finished\n");
}

int main(int argc, char *argv[]) {
  test_alarm();
  exit(0);
}
