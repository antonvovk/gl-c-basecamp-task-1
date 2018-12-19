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
    char port[10] = {'\0'}, ip_address[20] = {'\0'};
    printf("Enter server ip: ");
    scanf("%s", ip_address);
    printf("Enter server port: ");
    scanf("%s", port);

    if (createSocketClient(&socket_id, port, "127.0.0.1") == -1) {
        printf("[-] Couldn't connect to server %s on port %s...", ip_address, port);
        getchar();
        getchar();
        return -1;
    }

    callFuncPeriodically(2, sendData, 1, socket_id);
    return 0;
}

#endif


