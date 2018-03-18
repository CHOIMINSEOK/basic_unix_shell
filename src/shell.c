#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define FORK_ERROR -1
#define ON_CHILD 0
const char* SHELL_NAME = "prompt>";


int main(int argc, char **argv) {
	
	char command[50];
	char *arg[] = {0,};
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
				arg[0] = &command;
				arg[1] = NULL; 
				execvp(command, arg);	
				break;
			default :
				printf("on parent process : %d with child : %d\n", getpid(), pid);
		}
	}
}
