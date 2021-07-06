#ifndef __THREADS_H__
#define __THREADS_H__

#include <pthread.h>

#define SHARED_INIT {PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER}

struct shared {
    pthread_mutex_t mtime;
    pthread_mutex_t ctl;
    pthread_t inter_thr;
    int locked;
    unsigned time;
};

unsigned get_time(struct shared *shr);
void set_time(unsigned time, struct shared *shr);
void request(struct shared *shr);
int lock_ctl(struct shared *shr);
int unlock_ctl(struct shared *shr);

#endif // #ifndef __THREADS_H__
