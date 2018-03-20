#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

#define FORK_ERROR -1
#define ON_CHILD 0
const char* SHELL_NAME = "prompt>";
const char* TOKEN = " ";

char** getInputParamArray(char* inputString);
char* getCopyString(char* string);

int main(int argc, char **argv) {
	
	char command[50];
	char** arg = NULL;
	int pid;

	while(1) {
		fputs(SHELL_NAME, stdout);
		gets(command);

		pid = fork();
	
		switch(pid){
			case FORK_ERROR : 
				perror("fork error: ");
				exit(0);
			case ON_CHILD : 
				printf("on child process : %d, command : %s\n", getpid(), command);
				arg = getInputParamArray(command);
				execvp(arg[0], arg);	
				break;
			default :
				printf("on parent process : %d with child : %d\n", getpid(), pid);
				wait(0);
		}
	}
}

char** getInputParamArray(char* inputString) {
	int ARRAY_SIZE_UNIT = 10;
	char ** inputParams = (char**) malloc(sizeof(char*)*ARRAY_SIZE_UNIT);
	char* ptr = strtok(inputString, TOKEN);
 	int i = 0, j = 0;

	inputParams[i++] = getCopyString(ptr);

	while(ptr=strtok(NULL, TOKEN)) {
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
