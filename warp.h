#ifdef __WARP_H
#define __WARP_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

void warp(char** cmd,char* dir,char* prev_dir);

#endif