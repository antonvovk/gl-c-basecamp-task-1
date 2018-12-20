#include "system_api.h"

#ifdef __unix__

#include "unix_network.h"

#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

#include "windows_network.h"

#endif

int main() {
    unsigned long long socket_id;
    char port[10] = {'\0'}, ip_address[20] = {'\0'};
    printf("Enter server ip: ");
    scanf("%s", ip_address);
    printf("Enter server port: ");
    scanf("%s", port);

    if (createSocketClient(&socket_id, port, ip_address) == -1) {
        printf("[-] Couldn't connect to server %s on port %s...", ip_address, port);
        closeSocket(socket_id);
        getchar();
        getchar();
        return -1;
    }
    printf("[!] Press q if you want to quit...");
    fflush(stdout);

    callFuncPeriodically(2, sendData, 1, socket_id);
    closeSocket(socket_id);
    return 0;
}
