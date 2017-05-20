//
//  Buffer.c
//  TCPClientC
//
//  Created by Денис on 06/02/2017.
//  Copyright © 2017 Den V Design. All rights reserved.
//

#include "Buffer.h"
#include <stdlib.h>


void initBuffer (Buffer *buffer, size_t length) {
    
    buffer->value   = malloc (sizeof (char) * length);
    buffer->length  = length;
    buffer->used    = 0;
}


void extendBuffer (Buffer *buffer) {
    
    size_t newLength  = buffer->length * BUFFER_SCALAR;
    char *newValue  = malloc (sizeof (char) * newLength);
    for (int count  = 0; count < buffer->length; count++) {
        newValue[count] = buffer->value[count];
    }
    
    buffer->length  = newLength;
    buffer->value   = newValue;
    
    return;
}
