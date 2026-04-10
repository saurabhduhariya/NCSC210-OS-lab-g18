#include "kernel/types.h"
#include "user/user.h"

int main() {
	int value=100;

	send(value);
	int received=recv();

	printf("Value sent: %d\n",value);
	printf("Value received: %d\n",received);

	exit(0);
}
