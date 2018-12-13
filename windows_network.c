#include "windows_network.h"

int initialiseWinsock(void) {
    WSADATA wsaData;
    int res = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (res != 0) {
        printf("[-] WSAStartup failed with error: %d\n", res);
        return -1;
    }
    else {
        printf("[+] WSAStartup initialised successfully...\n");
    }
    return 0;
}

int fillAddrInfo(struct addrinfo **result, struct addrinfo *hints, char *address, int server_type) {
    int res;

    if (server_type == 0) {
        res = getaddrinfo(address, DEFAULT_PORT, hints, result);
    }
    else {
        res = getaddrinfo(NULL, DEFAULT_PORT, hints, result);
    }

    if (res != 0) {
        printf("[-] Getaddrinfo failed with error: %d\n", res);
        WSACleanup();
        return -1;
    }
    else {
        printf("[+] Getaddrinfo exucuted successfully...\n");
    }

    return 0;
}

int createSocketClient(SOCKET *Socket) {
    *Socket = INVALID_SOCKET;
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    int res;

    initialiseWinsock();

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    fillAddrInfo(&result, &hints, "127.0.0.1", 0);

    for(ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        *Socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (*Socket == INVALID_SOCKET) {
            printf("[-] Socket failed with error: %d\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        res = connect(*Socket, ptr->ai_addr, (int)ptr->ai_addrlen);

        if (res == SOCKET_ERROR) {
            closesocket(*Socket);
            *Socket = INVALID_SOCKET;
            continue;
        }

        break;
    }

    printf("[+] Socket created successfully...\n");
    return 0;
}

int createServerSocket(SOCKET *Socket) {
    int iResult;
    SOCKET ListenSocket = INVALID_SOCKET, ClientSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL, hints;

    initialiseWinsock();

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    fillAddrInfo(&result, &hints, NULL, 0);

    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("[-] Socket failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return -1;
    }
    else {
        printf("[+] Socket created successfully...\n");
    }

    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("[-] Bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return -1;
    }
    else {
        printf("[+] Bind successfully...\n");
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("[-] Listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return -1;
    }
    else {
        printf("[+] Started listening...\n");
    }

    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("[-]Accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return -1;
    }
    else {
        printf("[+] Accept successfully...\n");
    }

    closesocket(ListenSocket);
    *Socket = ClientSocket;

    return 0;
}

int sendData(char *data, unsigned long long Socket) {
    int iResult = send(Socket, data, (int)strlen(data), 0 );
    if (iResult == SOCKET_ERROR) {
            printf("[-] Send failed with error: %d\n", WSAGetLastError());
            closesocket(Socket);
            WSACleanup();
            return 1;
        }
    return 0;
}

int readData(char *data, unsigned long long Socket) {
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int iResult = recv(Socket, recvbuf, recvbuflen, 0);
    if (iResult == SOCKET_ERROR) {
            printf("[-] Send failed with error: %d\n", WSAGetLastError());
            closesocket(Socket);
            WSACleanup();
            return 1;
        }
    data = recvbuf;
    printf("%s\n", recvbuf);
    return 0;
}

