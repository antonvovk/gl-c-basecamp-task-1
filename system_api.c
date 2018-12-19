#include "system_api.h"

int callFuncPeriodically(unsigned seconds, int (*func_ptr)(char *data, unsigned long long socket_id), unsigned mouse_cords, unsigned long long socket_id) {
    long x_prev, y_prev;
    char data[50] = {'\0'};
    char buffer[50] = {'\0'};
    getMousePos(&x_prev, &y_prev);

    while (1) {
        if (mouse_cords == 1) {
            long x, y;
            getMousePos(&x, &y);

            if(x_prev == x && y_prev == y) {
                sprintf(data, "[-] Passive(X: %ld, Y: %ld)", x, y);
            }
            else {
                sprintf(data, "[+] Active(X: %ld, Y: %ld)", x, y);
            }

            x_prev = x;
            y_prev = y;

            func_ptr(data, socket_id);
        }
        else {
            func_ptr(buffer, socket_id);
        }

        #ifdef __unix__

        sleep(seconds);

        #elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

        Sleep(1000*seconds);

        #endif
    }
}

int getMousePos(long *x, long *y) {
    #ifdef __unix__

    FILE *fp;
    char path[256];

    fp = popen("xdotool getmouselocation", "r");

    fgets(path, sizeof(path)-1, fp);

    pclose(fp);

    *x = strtol(path+2, NULL,10);

    char *tmp;
    tmp = strchr(path,'y');

    *y = strtol(path + (tmp-path+2), NULL, 10);

    #elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

    POINT point;
    GetCursorPos(&point);
    *x = point.x;
    *y = point.y;

    #endif

    return 0;
}
