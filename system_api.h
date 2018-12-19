#ifndef SYSTEM_API_H
#define SYSTEM_API_H

#ifdef __unix__

#include <unistd.h>

#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "user32.lib")
#include <windows.h>

#endif

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int callFuncPeriodically(unsigned seconds, int (*func_ptr)(char *data, unsigned long long socket_id), unsigned mouse_cords, unsigned long long socket_id);
int getMousePos(long *x, long *y);

#endif
