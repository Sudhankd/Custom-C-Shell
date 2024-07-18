#ifndef __RULE_H
#define __RULE_H

#include<stdio.h>
#include<stdlib.h>

void rule(char** arr,char* shell_invk_dir,char* prev_dir,int check_fore_back);
void warp(char** cmd,char* dir,char* prev_dir);

#endif