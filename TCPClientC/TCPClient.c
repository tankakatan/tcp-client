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
#include "dummies.h"
#include "errors.h"


#define ATON_ERROR 0


int createSocket () {
    return (int)withErrorTest (socket (PF_INET, SOCK_STREAM, 0), SOCKET_OPEN_ERROR, SocketOpenError);
}


int closeSocket (int socket) {
    return (int)withErrorTest (close (socket), SOCKET_OPEN_ERROR, SocketCloseError);
}


int initAddress (const char *address, uint16_t port, struct sockaddr_in *destination) {
        
    destination->sin_port    = htons (port);
    destination->sin_family  = AF_INET;
    
    return (int)withErrorTest (inet_aton (address, &(destination->sin_addr)), ATON_ERROR, AddressConversionError) ;
}


int createConnection (int socket, const struct sockaddr_in *address) {
    return (int)withErrorTest (connect (socket,(struct sockaddr *)address, sizeof (*address)),
                          CONNECTION_ERROR, ConnectionError);
}


int connectToAddressAndPort (const char *addressString, uint16_t port) {
    
    int socket = createSocket ();
    struct sockaddr_in *address = malloc (sizeof (struct sockaddr_in));
    initAddress (addressString, port, address);
    createConnection (socket, address);
    
    free ((struct sockaddr_in *)address);
    return socket;
}


int sendCString (int socket, const char *string, size_t length) {
    printf("Sending data: %s\n", string);
    return (int)withErrorTest ((int)send (socket, string, length, 0), SENDING_ERROR, SendingError);
}

int connectTo (const char *addressString, const char *portString) {
    
    int port = atoi (portString);
    
    printf ("Connecting to %s port %d...\n", addressString, port);
    int connection = connectToAddressAndPort (addressString, port);

    return connection;
    
}

int getResponse (int socket, char *buffer, size_t length) {
    
    ssize_t messageLength = withErrorTest (recv (socket, buffer, length, 0),
                                           RESPONSE_ERROR, ResponseError);

    if (messageLength < 0) {
        return RESPONSE_ERROR;
    }
    
    if (length < messageLength) {
        printf ("Warning: Buffer overflow. Buffer size: %ld / Message size: %ld\n\n",
                length, messageLength);
    }
    
    if (messageLength == 0) {
        printf ("Empty message recieved.\n\n");
    }
    
    printf ("Response: %s\n", buffer);
    
    return 0;
}


void sendDummy (const char *address, const char *port) {
    
    int socket = connectTo (address, port);
    
    char *headers = malloc (bufferSize);
    headerWithHost (address, headers);
    sendCString(socket, headers, bufferSize);
    
    char *response = malloc (bufferSize);
    getResponse (socket, response, bufferSize);
    
    free (headers);
    free (response);
    
    closeSocket (socket);
}
