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

// Define your utility functions here, these will most likely be functions that you call
// in your myshell.c source file

#define BUFFER_LEN 256

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

void cd(char *arg) {
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
}

void clr(void) {
    system("clear");
}

void dir(char *arg) {
    char cmd[BUFFER_LEN] = {0};
    strcpy(cmd, "ls ");
    // if there is something in arg, pass it as a param to ls
    if (strcmp(arg, "") != 0)
        strcat(cmd, arg);

    system(cmd);
}

void environ() {
    system("env");
}

void echo(char *arg) {
    printf("%s\n", arg);
}

void help() {
    // just hard coded
    char *help_output = "printf 'cd <directory> - Change the current default directory to <directory>. If the <directory> argument is not present, report the current directory. If the directory does not exist an appropriate error should be reported. This command should also change the PWD environment variable.\n\nclr - Clear the screen.\n\ndir <directory> - List the contents of directory <directory>.\n\nenviron - List all the environment strings.\n\necho <comment> - Display <comment> on the display followed by a new line (multiple spaces/tabs may be reduced to a single space).\n\nhelp - Display the user manual using the more filter.\n\npause - Pause operation of the shell until 'Enter' is pressed.\n\nquit - Quit the shell.\n' | more";

    system(help_output);
}

void unsopported_command(char *command, char *arg) {
    pid_t PID = 0;
    PID = fork();

    if (PID == -1) {
        fputs("Unable to create fork for command\n", stderr);
        return;
    }

    if (PID == 0) {
        char dir[BUFFER_LEN] = {0};
        getcwd(dir, sizeof(dir));
        strcpy(dir, "/myshell");

        int return_execl;
        // if an arg is empty don't use it
        if (strcmp(arg, "") == 0)
            return_execl = execl("/bin/ls", command, NULL);
        // if no arg is populated use it
        else
            return_execl = execl("/bin/ls", command, arg, NULL);


        printf("failed to exec command; returned %d\n", return_execl);
        return;
    }
}
