//
//  helpers.h
//  TCPClientC
//
//  Created by Денис on 15/01/2017.
//  Copyright © 2017 Den V Design. All rights reserved.
//


#ifndef helpers_h
#define helpers_h

typedef const char *cString;
typedef void (*CStringHandler)(cString, int);

#include <stdio.h>


void printError (cString name);
void printArgs (int argc, cString argv[]);
void printInOrder (cString, int count);

void foreachString (cString *strings, CStringHandler);

int countInt (int *array, size_t size);
int countChar (const char *array, size_t size);
int countCStrings (const char **array, size_t size);

#endif /* helpers_h */
