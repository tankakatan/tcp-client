//
//  errors.c
//  TCPClientC
//
//  Created by Денис on 18/01/2017.
//  Copyright © 2017 Den V Design. All rights reserved.
//


#include "errors.h"
#include <errno.h>
#include <string.h>


void reportError (int code) {
    
    char *description;
    switch (code) {
        case SocketError:               description = "Socket"; break;
        case AddressConversionError:    description = "Address conversion"; break;
        case PortConversionError:       description = "Port conversion"; break;
        case ConnectionError:           description = "Connection"; break;
        case ApplicationError:          description = "Application"; break;
        default:                        description = "Unknown"; break;
    }
    
    printf ("Error %d: %s failed, %s\n\n", code, description, strerror (errno));
};

int reportIfEqual (int value, int to, enum Error errorType) {
    
//    printf ("Testing if %d\t==\t%d\t\t=> %d\n", value, to, value == to);
    if ((value == to) != 0) { reportError (errorType); }
    return value;
}
