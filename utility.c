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
    printf("this is the help, some more help. and helping");
}
