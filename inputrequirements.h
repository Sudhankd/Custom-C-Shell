#ifndef __INPUTREQUIREMENTS_H
#define __INPUTREQUIREMENTS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void input(char* shell_invok_dir,char* prev_dir);

void addcommand(char* lineptr,char* shell_invok_dir);
// void twosubpart(char **argv, char *token, char *delimitter);
// void warp(char** cmd,char str,char* dir,char* prev_dir,int len);
// int twosubpart(char **, char *, char *);

#endif