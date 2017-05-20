//
//  dummies.c
//  TCPClientC
//
//  Created by Денис on 19/01/2017.
//  Copyright © 2017 Den V Design. All rights reserved.
//


#include "dummies.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "errors.h"

int headerWithHost (const char *host, char *headers) {
    return (int)withErrorTest (sprintf (headers, dummyHTTPRequestFormat, host),
                               DUMMY_ERROR, 0);
}
