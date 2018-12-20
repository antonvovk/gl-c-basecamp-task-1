#include "unix_network.h"

int createSocket(int *socket_id) {
    *socket_id = socket(AF_INET, SOCK_STREAM, 0);

    if (*socket_id == -1) {
        printf("[-] Socket creation failed...\n");
        return -1;
    }
    else {
        printf("[+] Socket successfully created...\n");
    }

    return 0;
}

int createSocketClient(int *socket_id, int port, char *address) {
    struct sockaddr_in servaddr;

    createSocket(socket_id);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(address);
    servaddr.sin_port = htons(port);

    connectToServer(*socket_id, servaddr);

    return 0;
}

int connectToServer(unsigned long long socket_id, struct sockaddr_in servaddr) {
    if (connect(socket_id, (const struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
        printf("[-] Connection with the server failed...\n");
        return -1;
    }
    else {
        printf("[+] Connected to the server...\n");
    }

    return 0;
}

int createSocketServer(int *socket_id, int port) {
    struct sockaddr_in servaddr, cli;

    createSocket(socket_id);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if ((bind(*socket_id, (const struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
        printf("[-] Socket bind failed...\n");
        return -1;
    }
    else {
        printf("[+] Socket successfully binded...\n");
    }

    if ((listen(*socket_id, 5)) != 0) {
        printf("[-] Listen failed...\n");
        return -1;
    }
    else {
        printf("[+] Server listening...\n");
    }

    socklen_t len = sizeof(cli);
    int connfd = accept(*socket_id, (struct sockaddr*)&cli, &len);
    if (connfd < 0) {
       printf("[-] Server acccept failed...\n");
       return -1;
    }
    else {
        printf("[+] Server acccept the client...\n");
    }

    *socket_id = connfd;
    return 0;
}

int sendData(char *data, unsigned long long socket_id) {
    write(socket_id, data, sizeof(data) + 30);
    return 0;
}

int readData(char *data, unsigned long long socket_id) {
    bzero(data, sizeof(data) + 30);
    read(socket_id, data, sizeof(data) + 30);
    printf("%s\n", data);
    fflush(stdout);

    return 0;
}
