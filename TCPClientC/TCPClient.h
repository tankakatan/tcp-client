//
//  TCPClient.h
//  TCPClientC
//
//  Created by Денис on 15/01/2017.
//  Copyright © 2017 Den V Design. All rights reserved.
//


#ifndef TCPClient_h
#define TCPClient_h

#include <stdio.h>


#define SOCKET_OPEN_ERROR -1
#define SOCKET_CLOSE_ERROR -1
#define CONNECTION_ERROR -1
#define SENDING_ERROR -1
#define RESPONSE_ERROR -1
#define ADDRESS_CONVERSION_ERROR -2
#define APP_ERROR -1

#define BUFFER_SIZE 1024


static const size_t bufferSize = BUFFER_SIZE * sizeof (char);


int createSocket ();
int closeSocket (int socket);

int connectToAddressAndPort (const char *addressString, uint16_t port);
int connectTo (const char *addressString, const char *portString);
int initAddress (const char *address, uint16_t port, struct sockaddr_in *destination);
int sendCString (int socket, const char *string, size_t length);
int getResponse (int socket, char *buffer, size_t length);

void sendDummy (const char *address, const char *port);


#endif /* TCPClient_h */
