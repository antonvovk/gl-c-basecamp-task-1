#ifndef UNIX_NETWORK_H
#define UNIX_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int createSocket(int port, int type_server, int *sockfd, struct sockaddr_in *servaddr) ;
int connectToServer(int sockfd, struct sockaddr_in servaddr);
int serverPart(int sockfd, struct sockaddr_in servaddr);
int sendDataToServer(char *data, int sockfd);
int readDataFromClient(char *data, int sockfd);

#endif
