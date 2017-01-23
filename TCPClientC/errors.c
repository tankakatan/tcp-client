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
#include <stdlib.h>


void errorDescription (int code, char *description) {
    
    char *type;
    switch (code) {
        case SocketOpenError        : type = "Socket opening";      break;
        case SocketCloseError       : type = "Socket closing";      break;
        case AddressConversionError : type = "Address conversion";  break;
        case PortConversionError    : type = "Port conversion";     break;
        case ConnectionError        : type = "Connection";          break;
        case SendingError           : type = "Sending";             break;
        case ResponseError          : type = "Response";            break;
        case HeaderCreation         : type = "Header creation";     break;
        case ApplicationError       : type = "Application";         break;
        default                     : type = "Unknown";             break;
    }
    
//    static char description[128];
    sprintf (description, "Error %d: %s failed", code, type);
    return;
}


void assert (int test, const char *description) {
    if (test == 0) {
        printf ("%s. %s.\n\n", description, strerror (errno));
    }
}


long withErrorTest (long value, int errorValue, enum Error errorType) {
    
//    printf ("Testing if %d\t==\t%d\t\t=> %d\n", value, to, value == to);
    
    char *description = malloc (sizeof (char) * 128);
    errorDescription (errorType, description);
    assert ((value != errorValue), description);
    
    free (description);
    return value;
}
