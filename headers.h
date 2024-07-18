#ifndef __HEADERS_H_
#define __HEADERS_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<string.h>
#include<sys/wait.h>
#include <dirent.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <assert.h>

#include "prompt.h"
#include "addcommand.h"
#include "inputrequirements.h"
#include "warp.h"
#include "pastevents.h"
#include "rule.h"
#include "seek.h"
#include "peek.h"
#include "twosubpart.h"
#include "proclore.h"

extern int matches_found;

#endif