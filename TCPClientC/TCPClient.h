//
//  TCPClient.h
//  TCPClientC
//
//  Created by Денис on 15/01/2017.
//  Copyright © 2017 Den V Design. All rights reserved.
//

#include <stdio.h>

#ifndef TCPClient_h
#define TCPClient_h

#define SOCKET_ERROR -1
#define CONNECTION_ERROR -1
#define ADDRESS_CONVERSION_ERROR -2
#define APP_ERROR -1


int createSocket ();
int connectTo (const char *addressString, uint16_t port);
int createConnection (int socket, const struct sockaddr_in *address);
int initAddress (const char *address, uint16_t port, struct sockaddr_in *destination);


#endif /* TCPClient_h */
