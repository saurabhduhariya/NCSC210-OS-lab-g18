#include "kernel/types.h"
#include "user/user.h"

int main()
{
 mylock_init();

 if(fork() == 0){
   for(int i = 0; i < 1000; i++){
     mylock_acquire();
     increment();
     mylock_release();
   }
   exit(0);
 }

 if(fork() == 0){
   for(int i = 0; i < 1000; i++){
     mylock_acquire();
     increment();
     mylock_release();
   }
   exit(0);
 }
 wait(0);
 wait(0);

 printf("Final counter: %d\n", getcounter());
 exit(0);
}
