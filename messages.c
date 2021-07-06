#include <stdio.h>
#include <stdlib.h>

#include "messages.h"

static const char * const msgs[ERR_LAST] = {
    ERR_MSG "invalid usage",
    ERR_MSG "pthread creation failed",
    ERR_MSG "mutex operation failed",
    ERR_MSG "sio_open failed",
    ERR_MSG "sio_start failed",
    ERR_MSG "opening alarm sound file failed",
    ERR_MSG "reading alarm sound file failed",
    ERR_MSG "closing alarm sound file failed",
    ERR_MSG "reading input stream failed",
    ERR_MSG "writing output stream failed",
    ERR_MSG "malloc failed"
};

static const unsigned codes[ERR_LAST] = {
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11
};

void err(enum error e, const char *msg) {
    fprintf(stderr, "%s\n", msgs[e]);
    if(msg != NULL)
        printf("%s\n", msg);
    exit(codes[e]);
}
