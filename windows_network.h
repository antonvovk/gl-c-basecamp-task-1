#ifndef WINDOWS_NETWORK_H
#define WINDOWS_NETWORK_H

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

int initialiseWinsock(void);
int fillAddrInfo(struct addrinfo **result, struct addrinfo *hints, char *address, int server_type, char *port);
int createSocketClient(SOCKET *socket_id, char *port, char *address);
int createSocketServer(SOCKET *socket_id, char *port);
int sendData(char *data, unsigned long long socket_id);
int readData(char *data, unsigned long long socket_id);

#endif
