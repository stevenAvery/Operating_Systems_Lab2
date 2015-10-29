/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, 100493227
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here


int main(int argc, char *argv[])
{
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };

    // Parse the commands provided using argc and argv
    printf("> ");

    // Perform an infinite loop getting command input from users
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL) {
        // Perform string tokenization to get the command and argument
        tokenize((char *)buffer, &command, &arg);

        // Check the command and execute the operations for each command
        // cd command -- change the current directory
        if (strcmp(command, "cd") == 0) {
            cd(arg);

        // clr command -- clear the console
        } else if (strcmp(command, "clr") == 0) {
            clr();

        // dir command -- list the contents of directory
        } else if (strcmp(command, "dir") == 0) {
            dir(arg);

        // environ command -- list all the environment strings.
        } else if (strcmp(command, "environ") == 0) {
            environ();

        // echo command -- display comment, followed by newline
        } else if (strcmp(command, "echo") == 0) {
            echo(arg);

        // help command -- display user manual
        } else if (strcmp(command, "help") == 0) {
            help();

        // pause command -- pause the operation of the shell until Enter is pressed
        } else if (strcmp(command, "pause") == 0) {
            getchar();

        // quit command -- exit the shell
        } else if (strcmp(command, "quit") == 0) {
            return EXIT_SUCCESS;

        // Unsupported command
        } else {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }

        printf("> ");
    }
    return EXIT_SUCCESS;
}
