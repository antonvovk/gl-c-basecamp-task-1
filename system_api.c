#include "system_api.h"

int callFuncPeriodically(unsigned seconds, int (*func_ptr)()) {
    time_t start_time = time(NULL);
    while (1) {
        time_t now = time(NULL);

        time_t diff = now - start_time;

        if (diff  > seconds) {
            func_ptr();
            start_time = time(NULL);
        }
    }
}

int getMousePos(int *x, int *y) {
    #ifdef __unix__

    FILE *fp;
    char path[256];

    fp = popen("xdotool getmouselocation", "r");

    fgets(path, sizeof(path)-1, fp);

    pclose(fp);

    *x = strtol (path+2, NULL,10);

    char *tmp;
    tmp = strchr(path,'y');

    *y = strtol (path + (tmp-path+2), NULL, 10);

    #elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

    POINT point;
    GetCursorPos(&point);
    *x = point.x;
    *y = point.y;

    #endif
}
