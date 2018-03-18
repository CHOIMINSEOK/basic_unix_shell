# Implement basic unix shell

- Shell can be run in two ways: Interactive mode & Batch mode
- In interactive mode, shell displays a prompt and user types in a command at the prompt.
- Each line may contain multiple commands separated with the ; character.
- Each commands separated by ; character should be run simultaneously. It means that multiple processes run their command concurrently and parent process should wait all children before printing the next prompt.
- In batch mode, shell is started by specifying a batch file on its command line. The batch file contains the list of commands that should be executed.
