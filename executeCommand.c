#include "header.h"
/**
 * executeCommand - Executes a command with arguments.
 * @command: The command to execute.
 * @args: An array of strings containing the command's arguments
 * @path_copy: A copy of the path environment variable.
 * Return: 0 on success
 */

int executeCommand(__attribute__((unused))char *command, char *args[], char *path_copy)
{
	pid_t pid = fork();
	int command_found = 0;
	if (pid == 0)
	{ 
		/* Child Process right here */
		if (strchr(args[0], '/') != NULL)
		{
			execve(args[0], args, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			char *token, *cmd;
			char local_path_copy[1024];
			strncpy(local_path_copy, path_copy, sizeof(local_path_copy));
			token = strtok(local_path_copy, ":");
			while (token != NULL)
			{
				cmd = malloc(strlen(token) + strlen(args[0]) + 2);
				sprintf(cmd, "%s/%s", token, args[0]);
				if (access(cmd, X_OK) == 0)
				{
					command_found = 1;
					execve(cmd, args, NULL);
					perror("execve");
					exit(EXIT_FAILURE);
				}
				free(cmd);
				token = strtok(NULL, ":");
			}
			if (!command_found)
			{
				fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
				exit(127);
				/* Exit with status 127 for command not found */
			}
		}
	}
	else if (pid > 0)
	{
		/* This is the parent process */
		int status;
		wait(&status);
		if (WIFEXITED(status))
			{
				return (WEXITSTATUS(status));
			}
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (0);
}
