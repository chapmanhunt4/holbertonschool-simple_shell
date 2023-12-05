#include "header.h"

/**
 * copyFile - Copies a file.
 * @source: Source file to copy
 * @destination: Destination of the new file.
*/
void copyFile(char *source, char *destination)
{
    char *cpArgs[4];

    cpArgs[0] = "cp";
    cpArgs[1] = source;
    cpArgs[2] = destination;
    cpArgs[3] = NULL;
    if (execve("/bin/cp", cpArgs, NULL) == -1)
    {
        perror("execve");
        exit(EXIT_FAILURE);
    }
}
