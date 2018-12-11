#ifdef __unix__

#include "unix_network.h"

#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

#include "windows_network.h"

#endif

#include "system_api.h"

int main() {

    int sockfd;
    struct sockaddr_in servaddr;
    createSocket(5548, 0, &sockfd, &servaddr);
    connectToServer(&sockfd, &servaddr);

    int x, y;
    getMousePos(&x, &y);
    char buffer[20];
    sprintf(buffer, "%d %d", x, y);

    sendDataToServer(&sockfd, buffer);

    close(sockfd);

    return 0;
}
