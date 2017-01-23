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
#include "dummies.h"


//#ifndef DEBUG
//#define DEBUG 0
//#endif


int main(int argc, const char *argv[]) {
    
    
#ifdef DEBUG
    
    if (DEBUG != 0) {
        printArgs (argc, argv);
        if (test () == 0) { return 0; }
    }

#endif
    
    if (argc < 3) {
        printf ("Missing parameters.\n"
                "Please provide an IP address and a "
                "Port number for connection.\n\n");

    } else {
        
        sendDummy (argv[1], argv[2]);
    }
    
    return 0;
}
