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

#define DUMMY_ERROR -1

int headerWithHost (const char *host, char *headers) {
    return (int)withErrorTest (sprintf (headers, dummyHTTPHeaderFormat, host), DUMMY_ERROR, 0);
}