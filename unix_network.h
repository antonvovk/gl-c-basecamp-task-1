#ifndef UNIX_NETWORK_H
#define UNIX_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>

int createSocket(int *socket_id);
int createSocketClient(int *socket_id, int port, char *address);
int connectToServer(unsigned long long socket_id, struct sockaddr_in servaddr);
int createSocketServer(int *socket_id, int port);
int sendData(char *data, unsigned long long socket_id);
int readData(char *data, unsigned long long socket_id);

#endif
