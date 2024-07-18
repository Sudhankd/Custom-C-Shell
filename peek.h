#ifndef __PEEK_H
#define __PEEK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <assert.h>
#define dir_color "\x1b[34m"
#define file_color "\x1b[37m"
#define other "\x1b[37m"
#define exe_color "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

int comparator(const void *, const void *);
void mode_to_text(mode_t mode, char *text);
void format_time(const struct stat *st, char *formatted_time);

void peek(char **argv,char* shell_invk_dir);

#endif