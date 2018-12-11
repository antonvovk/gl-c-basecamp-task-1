#include "unix_network.h"

int createSocket(int PORT, int type_server, int *sockfd, struct sockaddr_in *servaddr) {

    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (*sockfd == -1) {
        printf("socket creation failed\n");
        exit(0);
    }
    else
        printf("Socket successfully created\n");

    servaddr->sin_family = AF_INET;
    if (type_server == 1)
        servaddr->sin_addr.s_addr = htonl(INADDR_ANY);
    else
        servaddr->sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr->sin_port = htons(PORT);
}

int connectToServer(int *sockfd, struct sockaddr_in *servaddr) {
    if (connect(*sockfd, servaddr, sizeof(*servaddr)) != 0) {
        printf("connection with the server failed\n");
        exit(0);
    }
    else
        printf("connected to the server\n");
}

int serverPart(int *sockfd, struct sockaddr_in *servaddr) {
    struct sockaddr_in cli;

    if ((bind(*sockfd, servaddr, sizeof(*servaddr))) != 0) {
        printf("socket bind failed\n");
        exit(0);
    }
    else
        printf("Socket successfully binded\n");

    if ((listen(*sockfd, 5)) != 0) {
        printf("Listen failed\n");
        exit(0);
    }
    else
        printf("Server listening\n");
    int len = sizeof(cli);


    int connfd = accept(*sockfd, (struct sockaddr*)&cli, &len);
    if (connfd < 0) {
       printf("server acccept failed\n");
       exit(0);
    }
    else
        printf("server acccept the client\n");
    return connfd;
}

int sendDataToServer(int *sockfd, char *buff) {
    write(*sockfd, buff, sizeof(buff));
}

int readDataFromClient(char *buff, int *sockfd) {
    read(*sockfd, buff, sizeof(buff));
    printf("%s", buff);
}
