#include "system_api.h"

#ifdef __unix__

#include "unix_network.h"

int main() {
    int socket;
    createSocketClient(&socket, 5577, "127.0.0.1");
    callFuncPeriodically(2, sendData, 1, socket);
    close(socket);
    return 0;
}

#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

#include "windows_network.h"

int main() {
    SOCKET socket_id;
    createSocketClient(&socket_id, "5577", "127.0.0.1");
    callFuncPeriodically(2, sendData, 1, socket_id);
    return 0;
}

#endif


