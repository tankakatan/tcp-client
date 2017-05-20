//
//  Buffer.h
//  TCPClientC
//
//  Created by Денис on 06/02/2017.
//  Copyright © 2017 Den V Design. All rights reserved.
//

#ifndef Buffer_h
#define Buffer_h

#include <stdio.h>

#define BUFFER_SCALAR 2
#define INITIAL_BUFFER_LENGTH 128

typedef struct {

    char *value;
    size_t length;
    size_t used;

} Buffer;


void initBuffer (Buffer *buffer, size_t length);
void extendBuffer (Buffer *buffer);


#endif /* Buffer_h */
