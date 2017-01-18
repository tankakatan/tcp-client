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
    SocketError = 121,
    AddressConversionError = 144,
    PortConversionError = 169,
    ConnectionError = 196,
    ApplicationError = 225,
};


void reportError (int code);
int reportIfEqual (int value, int systemCode, enum Error errorType);

#endif /* errors_h */
