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

#include <netinet/in.h>
#include <stdlib.h>

typedef int (*Test) ();
typedef Test *Tests;

int testSocket () {
    
    int socket = createSocket ();
    return socket != SOCKET_ERROR;
}


int testConnection () {
    
    int conection = connectTo (TEST_IP, TEST_PORT);
    return conection != CONNECTION_ERROR;
}


int testAddress () {
    struct sockaddr_in *address = malloc (sizeof (struct sockaddr_in));
    int conversion = initAddress (TEST_IP, TEST_PORT, address);
    int test = conversion != ADDRESS_CONVERSION_ERROR;
    
    free (address);
    return test;
}

int testCount () {
    int ints[4] = { 1, 2, 3, 4 };
    const char string[5] = "12345";
    const char *strings[3] = { "Hello", "world", "!!!" };
    
    return ((countInt (ints, sizeof (ints)) == 4) &&
            (countChar (string, sizeof (string)) == 5) &&
            (countCStrings (strings, sizeof (strings)) == 3));
}

Tests getTests () {
    
    static Test tests[5] = {
        testCount,
        testSocket,
        testAddress,
        testConnection,
        NULL,
    };
    
    return tests;
}

int test () {
    
    Tests tests = getTests();

    int count = 0;
    while (tests[count] != NULL) {
        if (tests[count++]() == 0) {
            printf ("Testing failed at Test %d\n\n", count);
            return 0;
        }
    }
    
    printf("Testing done\n");
    return 1;
}
