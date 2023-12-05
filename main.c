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
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *args[10];
    int i;

    if (isatty(STDIN_FILENO))
	    printf("Enter a command\n");
    while (getline(&buffer, &bufsize, stdin) != -1)
    {
	    printf("Enter a command\n");
	    getline(&buffer, &bufsize, stdin);
        /* Remove the trailing newline character */
        buffer[strcspn(buffer, "\n")] = '\0';
        /* If we don't set i to 0, it will only count up every time */
        /* the program is run and stop at 9 */
        i = 0;
        args[i] = strtok(buffer, " ");
        while (args[i] != NULL && i < 9)
        {
            i++;
            args[i] = strtok(NULL, " ");
        }
        /* Make sure the last element is NULL */
        args[i] = NULL;
        if (strcmp(args[0], "copy") == 0) {
            if (args[1] != NULL && args[2] != NULL)
            {
            /* Copy the file */
                copyFile(args[1], args[2]);
            }
            else
            {
                /* debugging. failure message, probably change this? */
                printf("Usage: copy source_file destination_file\n");
            }
	}
        else
        {
            /* Execute the command */
            executeCommand(args[0], args, path_copy);
        }
        free(path_copy);
        path_copy = strdup(path);
        printf("Enter a command\n");
    }
    free(buffer);
    free(path_copy);
    return (0);
}
