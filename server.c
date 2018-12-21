#include "system_api.h"

#ifdef __unix__

#include "unix_network.h"

#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

#include "windows_network.h"

#endif

int main() {
    unsigned long long socket_id;
    char port[10] = {'\0'};
    printf("Enter port: ");
    scanf("%s", port);

    createSocketServer(&socket_id, port);
    printf("[!] Press q if you want to quit...\n");
    fflush(stdout);

    callFuncPeriodically(2, readData, 0, socket_id);
    closeSocket(socket_id);
    return 0;
}
