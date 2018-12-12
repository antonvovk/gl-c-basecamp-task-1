#include "unix_network.h"

int createSocket(int port, int type_server, int *sockfd, struct sockaddr_in *servaddr) {
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (*sockfd == -1) {
        printf("[-] Socket creation failed\n");
        return -1;
    }
    else
        printf("[+] Socket successfully created\n");

    servaddr->sin_family = AF_INET;
    if (type_server == 1)
        servaddr->sin_addr.s_addr = htonl(INADDR_ANY);
    else
        servaddr->sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr->sin_port = htons(port);
    return 0;
}

int connectToServer(int sockfd, struct sockaddr_in servaddr) {
    if (connect(sockfd, (struct sockaddr_in*)&servaddr, sizeof(servaddr)) != 0) {
        printf("[-] Connection with the server failed\n");
        return -1;
    }
    else
        printf("[+] Connected to the server\n");

    return 0;
}

int serverPart(int sockfd, struct sockaddr_in servaddr) {
    struct sockaddr_in cli;

    if ((bind(sockfd, (struct sockaddr_in*)&servaddr, sizeof(servaddr))) != 0) {
        printf("[-] Socket bind failed\n");
        return -1;
    }
    else
        printf("[+] Socket successfully binded\n");

    if ((listen(sockfd, 5)) != 0) {
        printf("[-] Listen failed\n");
        return -1;
    }
    else
        printf("[+] Server listening\n");
    int len = sizeof(cli);


    int connfd = accept(sockfd, (struct sockaddr*)&cli, &len);
    if (connfd < 0) {
       printf("[-] Server acccept failed\n");
       return -1;
    }
    else
        printf("[+] Server acccept the client\n");

    return connfd;
}

int sendDataToServer(char *buff, int sockfd) {
    write(sockfd, buff, sizeof(buff) + 10);
}

int readDataFromClient(char *buff, int sockfd) {
    bzero(buff, sizeof(buff) + 10);
    read(sockfd, buff, sizeof(buff) + 10);
    printf("%s\n", buff);
    fflush(stdout);
}
