#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sndio.h>
#include <fcntl.h>

#include "timer.h"
#include "defaults.h"
#include "args.h"
#include "threads.h"
#include "inter.h"

#define PLAY_BUF_SIZE   (1024 * 128)

static void init(struct cmd_arg *arg, struct shared *shr) {
    if(parse_arg(arg)) {
        fprintf(stderr, "%s\n", ERR_USAGE_MSG);
        printf("%s\n", USAGE);
        exit(ERR_USAGE_CODE);
    }
    shr->time = arg->time;
}

static void mode(const struct cmd_arg *arg, struct shared *shr) {
    if( !(arg->flag & FLAG_INTER) )
        return;
    if( pthread_create(&shr->inter_thr, NULL, &inter, shr) ) {
        fprintf(stderr, "%s\n", ERR_PTHREAD_MSG);
        exit(ERR_PTHREAD_CODE);
    }
}

static void timer(struct shared *shr) {
    unsigned t = get_time(shr);
    while(t) {
        request(shr);
        while(sleep(1))
            ;
        set_time(--t, shr);
    }
}

static void play(struct sio_hdl *sio) {
    int fd;
    char buf[PLAY_BUF_SIZE];
    ssize_t i;
    if( -1 == (fd = open(ALARM_FILE_PATH, O_RDONLY)) ) {
        fprintf(stderr, "%s\n", ERR_AFILE_OPEN_MSG);
        exit(ERR_AFILE_OPEN_CODE);
    }
    while( (i = read( fd, buf, sizeof(buf) )) > 0 ) {
        ssize_t j;
        for( j = 0; i > j; j += sio_write(sio, buf + j, i - j) )
            ;
    }
    if(i == -1) {
        fprintf(stderr, "%s\n", ERR_AFILE_READ_MSG);
        exit(ERR_AFILE_READ_CODE);
    }
    if( -1 == close(fd) ) {
        fprintf(stderr, "%s\n", ERR_AFILE_CLOSE_MSG);
        exit(ERR_AFILE_CLOSE_CODE);
    }
}

static void alert(unsigned count) {
    unsigned i;
    struct sio_hdl *sio;
    if( NULL == (sio = sio_open(SIO_DEVANY, SIO_PLAY, 0)) ) {
        fprintf(stderr, "%s\n", ERR_SIO_OPEN_MSG);
        exit(ERR_SIO_OPEN_CODE);
    }
    if( 0 == sio_start(sio) ) {
        fprintf(stderr, "%s\n", ERR_SIO_START_MSG);
        exit(ERR_SIO_START_CODE);
    }
    play(sio);
    for(i = 2; i <= count; i++) {
        unsigned t = ALARM_TIMEOUT;
        while(t)
            t = sleep(t);
        play(sio);
    }
    sio_close(sio);
}

int main(const int argc, const char * const * const argv) {
    struct cmd_arg arg = CMD_ARG_INIT(argc, argv);
    struct shared shr = SHARED_INIT;
    init(&arg, &shr);
    mode(&arg, &shr);
    timer(&shr);
    alert(arg.repeat_count);
    return 0;
}
