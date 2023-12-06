#include "header.h"

/**
 * executeCommand - Executes a command with arguments.
 * @command: The command to execute.
 * @args: An array of strings containing the command's arguments
 * @path_copy: A copy of the path environment variable.
*/
void executeCommand(__attribute__((unused))char *command, char *args[], char *path_copy)
{	
	pid_t pid = fork();
    if (pid == 0) { /* Child process */
	    printf("Successfully forking \n");
        if (strchr(args[0], '/') != NULL) {
            /* Execute the command directly if it contains '/' */
            if (execve(args[0], args, NULL) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            char *token = strtok(path_copy, ":");
            while (token != NULL)
            {
                char cmd[1024];
                snprintf(cmd, sizeof(cmd), "%s/%s", token, args[0]);
                /*Remove newline, would ruin new file creation */
                cmd[strcspn(cmd, "\n")] = '\0';
                if (access(cmd, X_OK) == 0)
                {
			/* Create an array to store the enviornment variables */
			char *envp[] = {NULL};
                    /* Execute the command with arguments and environment */
                    if (execve(cmd, args, envp) == -1)
                    {
                        perror("execve");
                        exit(EXIT_FAILURE);
                        }
                }
                token = strtok(NULL, ":");
            }
            printf("Command not found in PATH: %s\n", args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0)
    {
     /* Parent process, wait for the child process */
        int status;
        wait(&status);
    }
    else
    {
        /* Fork failed */
        perror("fork");
        exit(EXIT_FAILURE);
    }
}
