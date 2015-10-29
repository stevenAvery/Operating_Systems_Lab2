/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#ifndef UTILITY_H_
#define UTILITY_H_

// Include your relevant functions declarations here they must start with the
// extern keyword such as in the following example:
// extern void display_help(void);

extern void tokenize(char *input, char **command, char **tokens);

extern void cd(char *arg);

extern void clr(void);

extern void dir(char *arg);

extern void environ();

extern void echo(char *arg);

extern void help();


#endif /* UTILITY_H_ */
