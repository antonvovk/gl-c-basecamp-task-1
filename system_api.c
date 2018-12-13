#include "system_api.h"

int callFuncPeriodically(unsigned seconds, int (*func_ptr)(char *data, unsigned long long sockfd), int mouse_cords, unsigned long long sockfd) {
    int x_prev, y_prev;
    char *data;
    char buffer[20];
    getMousePos(&x_prev, &y_prev);

    while (1) {
        if (mouse_cords == 1) {
            int x, y;
            getMousePos(&x, &y);

            if(x_prev == x && y_prev == y) {
                data = "[-] Passive";
            }
            else {
                data = "[+] Active";
            }

            x_prev = x;
            y_prev = y;

            //char buffer[20] = {'\0'};
            //sprintf(buffer, "%d %d", x, y);

            func_ptr(data, sockfd);
        }
        else {
            func_ptr(buffer, sockfd);
        }

        #ifdef __unix__

        sleep(seconds);

        #elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

        Sleep(1000*seconds);

        #endif
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

    return 0;
}
