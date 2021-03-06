/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, 100493227, 100451291, 100462413, 100522340
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


// tokenize the buffer
void tokenize(char *buffer, char *command[BUFFER_LEN], char *tokens[BUFFER_LEN]) {
    // remove the '\n' from the buffer
    char *clean_buffer;
    if ((clean_buffer = strtok(buffer, "\n")) == NULL)
        fputs("error: bad buffer, expected newline char\n", stderr);

    // take the first token as the command
    char *command_str;
    if ((command_str = strtok(clean_buffer, " ")) != NULL) {
        strcpy((char*)command, command_str);
    } else {
        strcpy((char*)command, "");
    }

    // put the rest of the buffer into 'tokens'
    char *token_str;
    if ((token_str = strtok(NULL, "")) != NULL) {
        strcpy((char*)tokens, token_str);
    } else {
        strcpy((char*)tokens, "");
    }
}

// cd command -- change the current directory
void cd(char *arg) {
    // get our current working directory
    char cwd[BUFFER_LEN] = {0};
    getcwd(cwd, sizeof(cwd));

    // if no arg is given just print current dir
    if (strcmp(arg, "") == 0 || strstr(arg, ">") != NULL) {
        strcat(cwd, arg); // incase of output redirection
        echo(cwd);

    // if an arg is given, set the environment variable 'PWD'
    } else {
        // try to change directory, and check if it was successful
        if (chdir(arg) == -1) {
            fputs("Unable to change directory\n", stderr);
        } else {
            // update the PWD environment var to match the current dir
            strcat(cwd, "/");
            strcat(cwd, arg);
            setenv("PWD", cwd, 1);
        }
    }
}

// clr command -- clear the console
void clr(void) {
    system("clear");
}

// dir command -- list the contents of directory
void dir(char *arg) {
    char cmd[BUFFER_LEN] = "ls ";
    strcat(cmd, arg);

    system(cmd);
}

// environ command -- list all the environment strings
void environ(char *arg) {
    char cmd[BUFFER_LEN] = "env ";
    strcat(cmd, arg);

    system(cmd);
}

// echo command -- display comment, followed by newline
void echo(char *arg) {
    char output_command[BUFFER_LEN] = "echo ";
    strcat(output_command, arg);

    system(output_command);
}

// help command -- display user manual
void help(char *arg) {
    // just hard coded
    char help_output[701 + BUFFER_LEN] = {0};
    strcat(help_output, "printf 'cd <directory> - Change the current default directory to <directory>. If the <directory> argument is not present, report the current directory. If the directory does not exist an appropriate error should be reported. This command should also change the PWD environment variable.\n\nclr - Clear the screen.\n\ndir <directory> - List the contents of directory <directory>.\n\nenviron - List all the environment strings.\n\necho <comment> - Display <comment> on the display followed by a new line (multiple spaces/tabs may be reduced to a single space).\n\nhelp - Display the user manual using the more filter.\n\npause - Pause operation of the shell until 'Enter' is pressed.\n\nquit - Quit the shell.\n' | more");

    strcat(help_output, arg);

    system(help_output);
}


// for QUESTION 2
// fork and exec any unsopported commands
void unsopported_command(char *command, char *arg) {
    // process id for the fork
    pid_t PID = 0;
    PID = fork();

    // error in creating the new process
    if (PID == -1) {
        fputs("Unable to create fork for command\n", stderr);
        return;
    }

    // the child process
    if (PID == 0) {
        // the path we would like our exec to use
        char dir[BUFFER_LEN] = {0};
        getcwd(dir, sizeof(dir));
        strcat(dir, "/myshell");

        // exec will exit, and return if anything goes wrong, this is to catch its return
        int return_execl;

        // if an arg is empty don't use it
        if (strcmp(arg, "") == 0)
            return_execl = execl(dir, command, NULL);
        // if no arg is populated use it
        else
            return_execl = execl(dir, command, arg, NULL);

        printf("failed to exec command; returned %d\n", return_execl);
        return;
    }
}
