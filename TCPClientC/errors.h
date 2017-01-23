//
//  errors.h
//  TCPClientC
//
//  Created by Денис on 18/01/2017.
//  Copyright © 2017 Den V Design. All rights reserved.
//


#ifndef errors_h
#define errors_h

#include <stdio.h>


enum Error {
    SocketOpenError         = 121,
    SocketCloseError        = 144,
    AddressConversionError  = 169,
    PortConversionError     = 196,
    ConnectionError         = 225,
    HeaderCreation          = 256,
    SendingError            = 289,
    ResponseError           = 324,
    ApplicationError        = 361,
};


void assert (int test, const char *description);
void errorDescription (int code, char *description);
long withErrorTest (long value, int errorValue, enum Error errorType);


#endif /* errors_h */
