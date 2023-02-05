#ifndef __INIT_H__
#define __INIT_H__

#include "file.h"

#define NET_INIT_SIZE 1 * 1024 * 1024

extern int language, enter_button, date_format, time_format;

void initSceAppUtil();

void finishSceAppUtil();

#endif
