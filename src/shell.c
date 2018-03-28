#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <fcntl.h>

#define FORK_ERROR -1
#define ON_CHILD 0

const char* SHELL_NAME = "prompt>";
const char* PARAM_TOKEN = " ";
const char* CMD_TOKEN = ";\n";
const int BUFFER_SIZE = 1024;

char** getInputParamArray(char* inputString);
char* getCopyString(char* string);

int main(int argc, char **argv) {
	
	char input[BUFFER_SIZE];
	char* command = NULL;
	char** arg = NULL;
	int pid, fd;
	

	if(argc==2) {
		if((fd=open(argv[1], O_RDONLY))==-1) return 0;
		else {
			read( fd, input, BUFFER_SIZE);
			close(fd);
		}
	}

	while(1) {
		int	childNum = 0;

		if(argc==1){
			fputs(SHELL_NAME, stdout);
			if(gets(input)==NULL) return 0;
		}

		command = strtok(input, CMD_TOKEN);
		do {
			pid = fork();
			childNum++;

			switch(pid){
				case FORK_ERROR : 
					perror("fork error: ");
					exit(0);
				case ON_CHILD : 
					arg = getInputParamArray(command);
					execvp(arg[0], arg);
			} 	
		} while(command=strtok(NULL, CMD_TOKEN));


		while(childNum--) {
			wait(0);
		}

		if(argc==2) return 0;
	}
}

char** getInputParamArray(char* inputString) {
	int ARRAY_SIZE_UNIT = 10;
	char ** inputParams = (char**) malloc(sizeof(char*)*ARRAY_SIZE_UNIT);
	char* ptr = strtok(inputString, PARAM_TOKEN);
 	int i = 0, j = 0;

	inputParams[i++] = getCopyString(ptr);

	while(ptr=strtok(NULL, PARAM_TOKEN)) {
		if (ARRAY_SIZE_UNIT <= i) {
			ARRAY_SIZE_UNIT += ARRAY_SIZE_UNIT;
			realloc(inputParams, ARRAY_SIZE_UNIT);
		}
		
		inputParams[i++] = getCopyString(ptr);
	}

	return inputParams;
}

char* getCopyString(char* string) {
	char* ptr = (char*) malloc(sizeof(char)*(strlen(string)+1));
	strcpy(ptr, string);
	return ptr;
}
