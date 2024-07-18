#ifndef __SEEK_H
#define __SEEK_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#define dir_color "\x1b[34m"
#define file_color "\x1b[37m"
#define other "\x1b[37m"
#define exe_color "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

void seek(char **argv,char* shell_invok_dir,char* prev_dir);

void rec_dir(char* arr,char* target,char* homedir,int flag,char* buffer);

#endif