#ifndef __PASTEVENTS_H
#define __PASTEVENTS_H

#include<stdio.h>
#include<stdlib.h>

void pastevents(char** argv,char* shell_invok_dir,char* prev_dir);
void addcommand(char* lineptr,char* shell_invok_dir);
// void rule(char** argv);

#endif