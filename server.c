#include "system_api.h"

#ifdef __unix__

#include "unix_network.h"

int main() {
    int socket_id;
    createSocketServer(&socket_id, 5577);
    callFuncPeriodically(2, readData, 0, socket_id);
    close(socket_id);
    return 0;
}

#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

#include "windows_network.h"

int main() {
    SOCKET socket_id;
    createSocketServer(&socket_id, "5577");
    callFuncPeriodically(2, readData, 0, socket_id);
    return 0;
}

#endif
