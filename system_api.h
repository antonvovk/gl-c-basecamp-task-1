#ifndef SYSTEM_API_H
#define SYSTEM_API_H


#ifdef __unix__

#include <unistd.h>

#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

#include <windows.h>

#endif

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int callFuncPeriodically(unsigned seconds, int (*func_ptr)());
int getMousePos(int *x, int *y);

#endif
