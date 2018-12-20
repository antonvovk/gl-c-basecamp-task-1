#include "system_api.h"

int callFuncPeriodically(unsigned seconds, int (*func_ptr)(char *data, unsigned long long socket_id), unsigned mouse_cords, unsigned long long socket_id) {
    long x_prev, y_prev;
    char data[BUFFER_SIZE] = {'\0'};
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
            func_ptr(data, socket_id);
        }

        #ifdef __unix__

        struct termios term;
        tcgetattr(0, &term);

        struct termios term2 = term;
        term2.c_lflag &= ~ICANON;
        tcsetattr(0, TCSANOW, &term2);

        int byteswaiting;
        ioctl(0, FIONREAD, &byteswaiting);

        tcsetattr(0, TCSANOW, &term);

        if (byteswaiting > 0) {
            char c = getchar();
            if(c == 'q') {
                return 0;
            }
        }

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
