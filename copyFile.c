#include "header.h"
/**
 * copyFile - Copies a file.
 * @source: Source file to copy
 * @destination: Destination of the new file.
 */

void copyFile(char *source, char *destination)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		/*this is the child process */
		char *cpArgs[4];
		cpArgs[0] = "/bin/cp";
		cpArgs[1] = source;
		cpArgs[2] = destination;
		cpArgs[3] = NULL;
		execve(cpArgs[0], cpArgs, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		/*This is the parent process */
		int status;
		wait(&status);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}
