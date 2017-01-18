//
//  TCPClient.c
//  TCPClientC
//
//  Created by Денис on 15/01/2017.
//  Copyright © 2017 Den V Design. All rights reserved.
//


#include "TCPClient.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#include "helpers.h"
#include "errors.h"


#define ATON_ERROR 0


int createSocket () {
    return reportIfEqual (socket (PF_INET, SOCK_STREAM, 0), SOCKET_ERROR, SocketError);
}


int initAddress (const char *address, uint16_t port, struct sockaddr_in *destination) {
        
    destination->sin_port    = htons (port);
    destination->sin_family  = AF_INET;
    
    return reportIfEqual (inet_aton (address, &(destination->sin_addr)), ATON_ERROR, AddressConversionError) ;
}


int createConnection (int socket, const struct sockaddr_in *address) {
    return reportIfEqual (connect (socket,(struct sockaddr *)address, sizeof (*address)),
                          CONNECTION_ERROR, ConnectionError);
}


int connectTo (const char *addressString, uint16_t port) {
    
    int socket  = createSocket ();
    struct sockaddr_in *address = malloc (sizeof (struct sockaddr_in));
    initAddress (addressString, port, address);
    int connection = createConnection (socket, address);

    free (address);
    return connection;
}
