#include "header.h"

/**
 * main - Recreation of shell.
 *
 * Return: 0 On success.
 */

int main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t lineSize;
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *args[10];
	int i;

	while (1) {
		if (isatty(STDIN_FILENO))
		{
			printf("Enter a command\n");
		}

		lineSize = getline(&buffer, &bufsize, stdin);
		if (lineSize == -1) {
			if (feof(stdin)) {
			/* End of file (Or input?) Which stops the while loop */
				break;
			}
			else if (ferror(stdin))
			{
				/* This is an error. What should the error message be?*/
				perror("getline");
				break;
			}
		}

		/* Remove the newline */
		buffer[strcspn(buffer, "\n")] = '\0';
		i = 0;
		args[i] = strtok(buffer, " ");
		while (args[i] != NULL && i < 9)
		{
			i++;
			args[i] = strtok(NULL, " ");
		}
		args[i] = NULL;

		if (args[0] != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				/*We're quitting */
				free(buffer);
				free(path_copy);
				exit(0);
			}
			if (strcmp(args[0], "copy") == 0)
			{
				if (args[1] != NULL && args[2] != NULL)
				{
					copyFile(args[1], args[2]);
				}
				else
				{
					/*This is an error */
					printf("Unable to copy file.\n");
				}
			}
			else
			{
				executeCommand(args[0], args, path_copy);
			}
		}
	}

	free(buffer);
	free(path_copy);
	return (0);
}
