/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
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

// Define functions declared in myshell.h here
void tokenize(char *input, char **command, char **tokens);

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
            char cwd[BUFFER_LEN] = {0};
            getcwd(cwd, sizeof(cwd));

            if (strcmp(arg, "") == 0) { // print current directory if no arg is given
                printf("%s\n", cwd);
            } else {
                chdir(arg);

                // update the PWD environment var to match the current dir
                strcat(cwd, "/");
                strcat(cwd, arg);
                setenv("PWD", cwd, 1);
            }

        // clr command -- clear the console
        } else if (strcmp(command, "clr") == 0) {
            system("clear");

        // dir command -- list the contents of directory
        } else if (strcmp(command, "dir") == 0) {
            char cmd[BUFFER_LEN] = {0};
            strcpy(cmd, "ls ");
            // if there is something in arg, pass it as a param to ls
            if (strcmp(arg, "") != 0)
                strcat(cmd, arg);

            system(cmd);

        // environ command -- list all the environment strings.
        } else if (strcmp(command, "environ") == 0) {
            system("env");

        // echo command -- display comment, followed by newline
        } else if (strcmp(command, "echo") == 0) {
            printf("%s\n", arg);

        // help command -- display user manual
        } else if (strcmp(command, "help") == 0) {

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

// tokenize the buffer
void tokenize(char *input, char **command, char **tokens) {
    // remove the '\n' from the input
    char *clean_input;
    if ((clean_input = strtok(input, "\n")) == NULL)
        ; // err bad input

    // take the first token as the command
    char *command_str;
    if ((command_str = strtok(clean_input, " ")) != NULL) {
        strcpy((char*)command, command_str);
    } else {
        strcpy((char*)command, "");
    }

    // put the rest of the input in tokens
    char *token_str;
    if ((token_str = strtok(NULL, "")) != NULL) {
        strcpy((char*)tokens, token_str);
    } else {
        strcpy((char*)tokens, "");
    }

    //*tokens = strtok(NULL, "");
}
