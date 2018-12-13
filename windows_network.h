#ifndef WINDOWS_NETWORK_H
#define WINDOWS_NETWORK_H
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "4015"

int initialiseWinsock(void);
int fillAddrInfo(struct addrinfo **result, struct addrinfo *hints, char *address, int server_type);
int createSocketClient(SOCKET *Socket);
int createServerSocket(SOCKET *Socket);
int sendData(char *data, unsigned long long Socket);
int readData(char *data, unsigned long long Socket);

#endif
