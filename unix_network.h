#ifndef UNIX_NETWORK_H
#define UNIX_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include "unix_network.h"

int createSocket(int PORT, int type_server, int *sockfd, struct sockaddr_in *servaddr) ;

int connectToServer(int *sockfd, struct sockaddr_in *servaddr);

int serverPart(int *sockfd, struct sockaddr_in *servaddr);

int sendDataToServer(int *sockfd, char *buff);

int readDataFromClient(char *buff, int *sockfd);

#endif
