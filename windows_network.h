#ifndef WINDOWS_NETWORK_H
#define WINDOWS_NETWORK_H

#define WIN32_LEAN_AND_MEAN
#define BUFFER_SIZE 50

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

int initialiseWinsock(void);
int fillAddrInfo(struct addrinfo **result, struct addrinfo *hints, char *address, int server_type, char *port);
int createSocketClient(SOCKET *socket_id, char *port, char *address);
int createSocketServer(SOCKET *socket_id, char *port);
int sendData(char *data, unsigned long long socket_id);
int readData(char *data, unsigned long long socket_id);
int closeSocket(unsigned long long socket_id);

#endif
