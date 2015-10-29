/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, 100493227
 * All rights reserved.
 *
 */

#ifndef UTILITY_H_
#define UTILITY_H_

extern void tokenize(char *input, char **command, char **tokens);

// command calls for question 1
extern void cd(char *arg);
extern void clr(void);
extern void dir(char *arg);
extern void environ();
extern void echo(char *arg);
extern void help();

void unsopported_command(char *command, char *arg);


#endif /* UTILITY_H_ */
