//
//  helpers.c
//  TCPClientC
//
//  Created by Денис on 15/01/2017.
//  Copyright © 2017 Den V Design. All rights reserved.
//

#include "helpers.h"

#include <errno.h>
#include <string.h>


void printError (cString name) {
    printf ("%s error: %s\n", name, strerror (errno));
}


void printInOrder (cString string, int count) {
    printf ("%d. %s\n", count + 1, string);
}


void printArgs (int argc, cString argv[]) {
    foreachString (argv, printInOrder);
    printf ("\n");
}

void foreachString (cString *strings, CStringHandler call) {
    int count = 0;
    while (strings[count] != 0) {
        call (strings[count], count);
        count++;
    }
}

int count (void *array, size_t size, size_t itemSize, const char *format) {
    
    size_t total = size / itemSize;
//    for (size_t i = 0; i < total; i++) {
//        printf (format, array + itemSize);
//    }
//    
//    printf ("\n");
    return (int)total;
}

int countInt (int *array, size_t size) {
    
    return count (array, size, sizeof (int), "%d, ");
}

int countChar (const char *array, size_t size) {
    
    return count ((char *)array, size, sizeof (char), "%a, ");
}

int countCStrings (const char **array, size_t size) {
    
    return count ((char **)array, size, sizeof (const char *), "%s, ");
}
