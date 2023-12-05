#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Function to execute a command */
void executeCommand(char *command, char *args[], char *path_copy);

/* Function to copy a file */
void copyFile(char *source, char *destination);

#endif
