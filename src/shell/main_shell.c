#include "../../include/common.h"

int main(){
	char command[256];
	while(1) {
		printf("g18-shell> ");
		fgets(command,sizeof(command),stdin);

		command[strcspn(command,"\n")]=0;

		if(strcmp(command,"exit")==0){
			break;
		}

		char full_cmd[300];
		sprintf(full_cmd,"./bin/%s",command);
		system(full_cmd);
	}
	return 0;
}
