#include "kernel/types.h"
#include "user/user.h"

int main(){
	printf("Parent PID: %d\n",getppid());
	exit(0);
}
