#ifndef __TIMER_H__
#define __TIMER_H__

#include <pthread.h>

#define NAME    "timer"
#define USAGE   \
    NAME " [flags] [time]" "\n" \
    "flags" "\n" \
    "\t"    "-r" "\n" \
    "\t\t"  "repeating alarm times by default" "\n" \
    "\t"    "-R count" "\n" \
    "\t\t"  "repeating alarm count times" "\n" \
    "\t"    "-i | -I" "\n" \
    "\t\t"  "interactive or non-interactive mode" "\n" \
    "time" "\n" \
    "\t" "time in format Xd Xh Xm Xs"

#define INTER_PROMPT        "> "
#define INTER_INVCMD_MSG    "invalid command"
#define INTER_HELP_MSG      \
    "exit" "\t"     "unset timer and quit" "\n" \
    "help" "\t"     "help message" "\n" \
    "pause" "\t"    "pause timer" "\n" \
    "query" "\t"    "query remaining time" "\n" \
    "resume" "\t"   "resume timer"
#define INTER_PAUSED_MSG    "timer paused"
#define INTER_RESUMED_MSG   "timer resumed"

#define ERR                     NAME ": "
#define ERR_USAGE_MSG           ERR "invalid usage"
#define ERR_PTHREAD_MSG         ERR "pthread creation failed"
#define ERR_MUTEX_MSG           ERR "mutex operation failed"
#define ERR_SIO_OPEN_MSG        ERR "sio_open failed"
#define ERR_SIO_START_MSG       ERR "sio_start failed"
#define ERR_AFILE_OPEN_MSG      ERR "opening alarm sound file failed"
#define ERR_AFILE_READ_MSG      ERR "reading alarm sound file failed"
#define ERR_AFILE_CLOSE_MSG     ERR "closing alarm sound file failed"
#define ERR_READ_MSG            ERR "reading input stream failed"
#define ERR_WRITE_MSG           ERR "writing output stream failed"
#define ERR_MALLOC_MSG          ERR "malloc failed"

enum {
    ERR_USAGE_CODE = 1,
    ERR_PTHREAD_CODE,
    ERR_MUTEX_CODE,
    ERR_SIO_OPEN_CODE,
    ERR_SIO_START_CODE,
    ERR_AFILE_OPEN_CODE,
    ERR_AFILE_READ_CODE,
    ERR_AFILE_CLOSE_CODE,
    ERR_READ_CODE,
    ERR_WRITE_CODE,
    ERR_MALLOC_CODE
};

struct shared {
    pthread_mutex_t mtime;
    pthread_mutex_t ctl;
    pthread_t inter_thr;
    int locked;
    unsigned time;
};

#define SHARED_INIT {PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER}

unsigned get_time(struct shared *shr);

#endif
