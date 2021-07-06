#include "threads.h"
#include "messages.h"

static void lock(pthread_mutex_t *m) {
    if( pthread_mutex_lock(m) )
        err(ERR_MUTEX, NULL);
}

static void unlock(pthread_mutex_t *m) {
    if( pthread_mutex_unlock(m) )
        err(ERR_MUTEX, NULL);
}

unsigned get_time(struct shared *shr) {
    unsigned res;
    lock(&shr->mtime);
    res = shr->time;
    unlock(&shr->mtime);
    return res;
}

void set_time(unsigned time, struct shared *shr) {
    lock(&shr->mtime);
    shr->time = time;
    unlock(&shr->mtime);
}

void request(struct shared *shr) {
    lock(&shr->ctl);
    unlock(&shr->ctl);
}

int lock_ctl(struct shared *shr) {
    if(shr->locked)
        return 0;
    lock(&shr->ctl);
    shr->locked = 1;
    return 1;
}

int unlock_ctl(struct shared *shr) {
    if(!shr->locked)
        return 0;
    unlock(&shr->ctl);
    shr->locked = 0;
    return 1;
}
