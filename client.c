#include "system_api.h"

#ifdef __unix__

#include "unix_network.h"

int main() {
    int sockfd;
    struct sockaddr_in servaddr;

    createSocket(5576, 0, &sockfd, &servaddr);
    connectToServer(sockfd, servaddr);
    callFuncPeriodically(2, sendDataToServer, 1, sockfd);
    close(sockfd);

    return 0;
}

#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

#include "windows_network.h"

int main() {
    SOCKET Socket;
    createSocketClient(&Socket);
    callFuncPeriodically(2, sendData, 1, Socket);
    return 0;
}

#endif


