#include "system_api.h"

#ifdef __unix__

#include "unix_network.h"

int main() {
    int Socket;
    createSocketServer(&Socket, 5577);
    callFuncPeriodically(2, readData, 0, Socket);
    close(Socket);
    return 0;
}

#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

#include "windows_network.h"

int main() {
    SOCKET Socket;
    createServerSocket(&Socket);
    callFuncPeriodically(2, readData, 0, Socket);
    return 0;
}

#endif
