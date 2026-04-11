#include "../../include/common.h"
#include <getopt.h>

int main(int argc,char *argv[]){
	int opt;
	int lflag=0,wflag=0,cflag=0;

	while((opt=getopt(argc,argv,"lwc"))!=-1){
		switch(opt){
			case 'l': lflag=1; break;
			case 'w': wflag=1; break;
			case 'c': cflag=1; break;
			default:
				printf("Usage: g18-wc [-l] [-w] [-c] <file>\n");
				return 1;
		}
	}

	if(optind>=argc){
		printf("Usage: g18-wc [-l] [-w] [-c] <file>\n");
		return 1;
	}

	FILE *fp=fopen(argv[optind],"r");
	if(!fp){
		perror("Error in opening file");
		return 1;
	}

	int lines=0,words=0,chars=0;
	char ch,prev=' ';

	while((ch=fgetc(fp))!=EOF){
		chars++;

		if(ch=='\n'){
			lines++;
		}

		if((ch==' '||ch=='\n'||ch=='\t')&&(prev!=' '&&prev!='\n'&&prev!='\t')){
			words++;
		}

		prev=ch;
	}

	if(!lflag && !wflag && !cflag){
		printf("Lines: %d Words: %d Characters:%d\n",lines,words,chars);
	} else {
		if(lflag) {
			printf("Lines: %d\n",lines);
		}
		if(wflag) {
			printf("Words: %d\n",words);
		}
		if(cflag) {
			printf("Characters: %d\n",chars);
		}
	}

	fclose(fp);
	return 0;
}
	
