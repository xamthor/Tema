#ifndef __UTILS_H__
#define __UTILS_H__

#include "main.h"

void initPowerTickThread();

void powerLock();

void powerUnlock();

int hasEndSlash(char *path);

int removeEndSlash(char *path);

int addEndSlash(char *path);

#endif
