#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "inter.h"
#include "messages.h"
#include "threads.h"

#define BUF_SIZE    1024

struct buffer {
    char data[BUF_SIZE];
    ssize_t len;
    ssize_t pos;
};

/* enum type corresponds to cmds */
enum type {
    NOOP = 0,
    EXIT,
    HELP,
    PAUSE,
    QUERY,
    RESUME,
    LAST /* needed for counting */
};

/* cmds lexicographically ordered */
static const char * const cmds[] = {
    "",
    "exit",
    "help",
    "pause",
    "query",
    "resume"
};

static char* strexpand(char *str, ssize_t size, ssize_t delta) {
    char *t;
    ssize_t i;
    if(delta == 0)
        return str;
    if( NULL == (t = malloc(size + delta)) )
        err(ERR_MALLOC, NULL);
    for(i = 0; i < size; i++)
        t[i] = str[i];
    free(str);
    return t;
}

static int extract(struct buffer *buf, char **str) {
    char *res = strexpand(NULL, 0, 1);
    ssize_t size = 1;
    ssize_t i;
    do {
        ssize_t j, k;
        if(buf->pos >= buf->len) {
            buf->pos = 0;
            if( -1 == (buf->len = read(0, buf->data, sizeof(buf->data))) )
                err(ERR_READ, NULL);
        }
        if(buf->len == 0)
            break;
        for(i = buf->pos; (i < buf->len) && (buf->data[i] != '\n'); i++)
            ;
        res = strexpand(res, size, i - buf->pos);
        for(j = size - 1, k = buf->pos; k < i; j++, k++)
            res[j] = buf->data[k];
        size += i - buf->pos;
        buf->pos = i + 1;
    } while(i == buf->len);
    res[size - 1] = '\0';
    *str = res;
    return buf->len != 0;
}

static void inform(const char *fmt, ... ) {
    va_list args;
    va_start(args, fmt);
    if(vprintf(fmt, args) < 0)
        err(ERR_WRITE, NULL);
}

static void print_time(unsigned time) {
    inform(
            "%ud %uh %um %us remaining\n",
            time / (60 * 60 * 24),
            time / (60 * 60) % 24,
            time / 60 % 60,
            time % 60
          );
}

static void prompt(void) {
    inform("%s", INTER_PROMPT);
    if( EOF == fflush(stdout) )
        err(ERR_WRITE, NULL);
}

static int match(const char *str, const char *template) {
    ssize_t i;
    for(i = 0; str[i] && (str[i] == template[i]); i++)
        ;
    return str[i] == template[i] ? 1
                                 : (str[i] ? 0 : -1);
    /* "" is matched to any template */
}

static enum type eval(const char *str) {
    enum type i, j;
    int r;
    for(i = 0; (i < LAST) && ( 0 == (r = match(str, cmds[i])) ); i++)
        ;
    if(i == LAST) {
        inform("%s\n", INTER_INVCMD_MSG);
        return HELP;
    }
    if(r > 0)
        return i;
    for(j = i + 1; (j < LAST) && (match(str, cmds[j]) < 0); j++) 
        ;
    if(j - i > 1) {
        enum type k;
        for(k = i; k < j; k++)
            inform("%s\n", cmds[k]);
        return NOOP;
    }
    return i;
}

static void run(enum type type, struct shared *shr) {
    switch(type) {
    case NOOP:
        break;
    case HELP:
        inform("%s\n", INTER_HELP_MSG);
        break;
    case PAUSE:
        if( lock_ctl(shr) )
            inform("%s\n", INTER_PAUSED_MSG);
        print_time(get_time(shr));
        break;
    case QUERY:
        print_time(get_time(shr));
        break;
    case EXIT:
        print_time(get_time(shr));
        exit(0);
    case RESUME:
        if( unlock_ctl(shr) )
            inform("%s\n", INTER_RESUMED_MSG);
        print_time(get_time(shr));
        break;
    default:
        ;
    }
}

void* inter(void *arg) {
    struct shared *shr = (struct shared *) arg;
    struct buffer buf;
    int cont;
    buf.pos = buf.len = 0;
    pthread_detach(pthread_self());
    do {
        char *str;
        enum type type;
        prompt();
        cont = extract(&buf, &str);
        type = eval(str);
        run(type, shr);
        free(str);
    } while(cont);
    exit(0);
}
