//
//  main.c
//  TCPClientC
//
//  Created by Денис on 15/01/2017.
//  Copyright © 2017 Den V Design. All rights reserved.
//


#include <stdio.h>
#include "stdlib.h"
#include <unistd.h>

#include "TCPClient.h"
#include "testTCPClient.h"
#include "helpers.h"
#include "errors.h"

#define DEBUG 0

int main(int argc, const char *argv[]) {
    
    
#ifdef DEBUG
    if (DEBUG) {
#endif
        printArgs (argc, argv);
        if (test () == 0) { return 0; }
#ifdef DEBUG
    }
#endif
    
    if (countCStrings (argv, argc*(sizeof (const char *))) < 3) {
        printf ("Missing parameters. Please provide IP address and Port number.\n\n");

    } else {

        const char *address = argv[1];
        int port = atoi (argv[2]);

        printf ("Connecting to %s port %d...\n", address, port);
        int connection = connectTo (address, port);
        if (connection != CONNECTION_ERROR) {
            printf ("Connection opened at %s port %d\n", address, port);
            sleep (16);
            printf ("Connection closed.\n\n");
        }
    }
    
    return 0;
}
