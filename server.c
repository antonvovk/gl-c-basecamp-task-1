#ifdef __unix__

#include "unix_network.h"

#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

#include "windows_network.h"

#endif

#include "system_api.h"

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    createSocket(5548, 1, &sockfd, &servaddr);
    int conffd = serverPart(&sockfd, &servaddr);

    char buff[200];
    readDataFromClient(buff, &conffd);
    close(sockfd);
    return 0;
}
