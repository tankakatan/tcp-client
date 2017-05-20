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
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <regex.h>

#include <netdb.h>

#include "helpers.h"
#include "dummies.h"
#include "errors.h"


#define ATON_ERROR 0


int createSocket () {
    return (int)withErrorTest (socket (PF_INET, SOCK_STREAM, 0),
                               SOCKET_OPEN_ERROR, SocketOpenError);
}


int closeSocket (int socket) {
    return (int)withErrorTest (close (socket), SOCKET_OPEN_ERROR, SocketCloseError);
}


int initAddress (const char *address, uint16_t port, struct sockaddr_in *destination) {
        
    destination->sin_port    = htons (port);
    destination->sin_family  = AF_INET;
    
    return (int)withErrorTest (inet_aton (address, &(destination->sin_addr)),
                               ATON_ERROR, AddressConversionError);
}


int createConnection (int socket, const struct sockaddr_in *address) {
    return (int)withErrorTest (connect (socket, (struct sockaddr *)address, sizeof (*address)),
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
    printf("Sending data:\n\n%s\n\n", string);
    return (int)withErrorTest ((int)send (socket, string, length, 0),
                               SENDING_ERROR, SendingError);
}


int connectTo (const char *addressString, const char *portString) {
    
    int port = atoi (portString);
    
    printf ("\nConnecting to %s port %d...\n\n", addressString, port);
    int connection = connectToAddressAndPort (addressString, port);

    return connection;
    
}


#define MAX(a,b) ((a) > (b) ? a : b)

size_t getResponse (int socket, Buffer *buffer) {
    
    ssize_t messageLength = 0;
    do {
        
        messageLength = recv (socket, buffer->value + buffer->used, buffer->length - buffer->used, 0);
        buffer->used += withErrorTest (messageLength, RESPONSE_ERROR, ResponseError);
        if (buffer->used == buffer->length) { extendBuffer (buffer); }
    
    } while (messageLength > 0);
    
    buffer->value[buffer->used + 1] = 0;
    return buffer->used;
}


int isIPAddress (const char *string) {
    regex_t ipRegex;
    char *ipPattern = ("^(([0-9]|[1-9][0-9]|(1[0-9]{2}|(2[0-4][0-9]|25[0-6])))\\.){3}"
                         "([0-9]|[1-9][0-9]|(1[0-9]{2}|(2[0-4][0-9]|25[0-6])))$");
    
    int regexError = regcomp (&ipRegex, ipPattern, 0);
    if (regexError) {
        printf ("Unable to compile regular expression");
        return -1;
    }
    
    int regexMatching = regexec(&ipRegex, string, 0, NULL, 0);
    if (regexMatching == REG_NOMATCH) {
        printf("%s is not an IP address", string);
        return 1;
    
    } else if (regexMatching) {
        char buffer[128];
        regerror (regexMatching, &ipRegex, buffer, sizeof(buffer));
        printf("Regex matching error: %s", buffer);
        return 2;
    }
    
    printf("%s is valid IP address", string);
    return 0;
}


int getIPAddress (char *buffer, const char *address) {
    
    
//    if (isIPAddress(address) == 0) {
//        buffer = (char *)address;
//        return 0;
//    }
    
    struct addrinfo *addressList; //*addressItem;
    int error = getaddrinfo (address, NULL, NULL, &addressList);
    if (error != 0) {
        printf ("Host %s is unreachable: (%s)\n", address, gai_strerror (error));
        return -1;
    }
    
//    printf ("Received info about %s:\n", address);

//    for (addressItem = addressList; addressItem; addressItem = addressItem->ai_next) {
//        printf ("• %s\n", inet_ntoa (((struct sockaddr_in *)addressItem->ai_addr)->sin_addr));
//    }
    
//    addressItem = addressList;
//    while (addressItem) {
//        printf ("• %s\n", inet_ntoa (((struct sockaddr_in *)addressItem->ai_addr)->sin_addr));
//        addressItem = addressItem->ai_next;
//    }
    
    memcpy (buffer, inet_ntoa (((struct sockaddr_in *)addressList->ai_addr)->sin_addr),
            addressList->ai_addr->sa_len);

    freeaddrinfo (addressList);
//    printf("\nGrabbing first address %s\n\n", buffer);
    
    return sizeof (buffer);
}


int sendPartOfString (int socket, char* string, int offset, int length) {
  char *part = string + offset;
  return sendCString (socket, part, length);
}


void sendDummy (const char *addressString, const char *port) {
    
  char *address = malloc(14);
  if (getIPAddress (address, addressString) <= 0) {
      printf ("The host %s is unreachable", addressString);
      return;
  }
  
  int socket      = connectTo (address, port);
  char *request   = malloc (bufferSize);
  
  headerWithHost (address, request);
  
  Buffer buffer;
  initBuffer (&buffer, INITIAL_BUFFER_LENGTH);
  
//  sendCString (socket, request, bufferSize);
//  getResponse (socket, &buffer);
  
  int offset = 0, sent = 0, shouldSend = 1, shouldExit = 0;
  const int partLength = 2;
  char *requestPart = malloc (partLength + 1);
  
  ssize_t messageLength = 0;
  do {
    
    if (shouldSend && (offset < strlen (request))) {
      if (snprintf (requestPart, partLength + 1, "%s", request + offset) < 0) {
        perror ("Part of string error");
      } else {
        printf ("Sending part of string: %s...\n", requestPart);
        if ((sent = sendCString (socket, requestPart, partLength)) < 0) {
          perror("Send part error");
          shouldSend = 0;
        } else {
          offset += partLength;
          usleep (1000000);
        }
      }
    } else {

      messageLength = recv (socket, buffer.value + buffer.used, buffer.length - buffer.used, 0);
      if (messageLength > 0) {
        buffer.used += withErrorTest (messageLength, RESPONSE_ERROR, ResponseError);
        if (buffer.used == buffer.length) {
          extendBuffer (&buffer);
        }
      } else {
        shouldExit = 1;
      }
    }
    
  } while (!shouldExit);
  
  free (requestPart);
  free (request);

  buffer.value[buffer.used + 1] = 0;
//  return buffer.used;
  
  printf ("Response:\n\n%s\n\nLength: %ld of %ld\n\n",
          buffer.value, buffer.used, buffer.length);
  
  free (buffer.value);
  
  closeSocket (socket);
}
