//
//  testTCPClient.c
//  TCPClientC
//
//  Created by Денис on 15/01/2017.
//  Copyright © 2017 Den V Design. All rights reserved.
//


#include "testTCPClient.h"
#include "TCPClient.h"
#include "helpers.h"
#include "dummies.h"

#include <netinet/in.h>
#include <stdlib.h>


typedef int (*Test) ();
typedef const Test *Tests;



int testSocket () {
    
    int socket = createSocket ();
    if (socket == SOCKET_OPEN_ERROR) { return 0; }
    
    int result = closeSocket (socket);
    if (result == SOCKET_CLOSE_ERROR) { return 0; }
    
    return 1;
}


int testConnection () {
    
    int connection = connectToAddressAndPort (TEST_IP, TEST_PORT);
    if (connection == CONNECTION_ERROR) { return 0; };
    
    int result = closeSocket (connection);
    if (result == SOCKET_CLOSE_ERROR) { return 0; }
    
    return 1;
}


int testAddress () {
    struct sockaddr_in *address = malloc (sizeof (struct sockaddr_in));
    int conversion = initAddress (TEST_IP, TEST_PORT, address);
    int test = conversion != ADDRESS_CONVERSION_ERROR;
    
    free (address);
    return test;
}

//
//int testCount () {
//    int ints[4] = { 1, 2, 3, 4 };
//    char string[5] = "12345";
//    const char *strings[3] = { "Hello", "world", "!!!" };
//    
//    int result = ((countInt (ints, sizeof (ints)) == 4) &&
//            (countChar (string, sizeof (string)) == 5) &&
//            (countCStrings (strings, sizeof (strings)) == 3));
//    
//    return result;
//}

int testSend () {
    int socket = connectToAddressAndPort (TEST_IP, TEST_PORT);
    
    char *message = malloc (sizeof (char) * 128);
    int headersCreated = headerWithHost (TEST_IP, message);
    if (headersCreated == DUMMY_ERROR) {
        return 0;
    }
    
    int isSent = sendCString(socket, message, sizeof (message));
    if (isSent == SENDING_ERROR) {
        return 0;
    }
    
    closeSocket (socket);
    free (message);
    
    return 1;
}


int testResponse () {
    
    int socket = connectTo (TEST_IP, TEST_PORT_STRING);

    char *message = malloc (bufferSize);
    headerWithHost (TEST_IP, message);
    sendCString (socket, message, bufferSize);
    
    char *response = malloc (bufferSize);
    size_t received = getResponse (socket, response, bufferSize);
    
    closeSocket (socket);
    free (message);
    free (response);
    
    return received != -1;
}


static const Test tests[5] = {
    testSocket,
    testAddress,
    testConnection,
    testSend,
    testResponse,
};


int test () {
    
    for (int i = 0; i < sizeof (tests)/ sizeof (Test); i++) {

        const Test test = tests[i];
        if (test() == 0) {
            printf ("Testing failed at Test %d\n\n", i + 1);
            return 0;
        }
    }
    
    printf("Testing done.\n\n");
    return 1;
}
