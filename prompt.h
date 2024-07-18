#ifndef __PROMPT_H
#define __PROMPT_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void prompt();

void sigchld_handler(int signo);
// void command_exe(char** cmd,char str,char* dir,char* prev_dir,int len);

// void peek(char** argv);
// char* get_location(char* cmd);

#endif