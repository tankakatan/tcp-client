//
//  dummies.h
//  TCPClientC
//
//  Created by Денис on 19/01/2017.
//  Copyright © 2017 Den V Design. All rights reserved.
//

#ifndef dummies_h
#define dummies_h

#include <stdio.h>


#define DUMMY_ERROR -1


static const char *dummyHTTPHeaderFormat =
    "GET / HTTP/1.1\r\n"
    "Host: %s\r\n\r\n";

//    "User-Agent: "
//        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_2) "
//        "AppleWebKit/537.36 (KHTML, like Gecko) "
//        "Chrome/55.0.2883.95 Safari/537.36\r\n"
//    "Accept: text/html,application/xhtml+xml,"
//        "application/xml;q=0.9,*/*;q=0.8\r\n"
//    "Accept-Language: en-us,en;q=0.5\r\n"
//    "Accept-Encoding: gzip,deflate\r\n"
//    "Accept-Charset: utf-8\r\n"
//    "Pragma: no-cache\r\n"
//    "Cache-Control: no-cache\r\n\r\n";

int headerWithHost (const char *host, char *headers);

/*
    "Keep-Alive: 300\r\n"                                   \
    "Connection: keep-alive\r\n"                            \
*/


#endif /* dummies_h */
